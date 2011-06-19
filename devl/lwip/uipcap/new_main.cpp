#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#ifndef WINVER
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT WINVER
#endif
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else /* WIN32 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif /* WIN32 */

#ifdef AF_LINK
#include <net/if_dl.h>
#endif /* AF_LINK */

#ifdef AF_PACKET
#include <netpacket/packet.h>
#endif /* AF_PACKET */

#include "lwipcap.h"

void log(const char *logstr)
{
  fprintf(stdout, "Log: %s\n", logstr);
}

void error(const char *errstr)
{
  fprintf(stderr, "Error: %s\n", errstr);
}

char *familyToString(struct sockaddr *sock, char *family)
{
  if (sock == NULL) {
    strcpy(family, "N/A");
  }
  else if (sock->sa_family == AF_INET) {
    strcpy(family, "IPv4");
  }
  else if (sock->sa_family == AF_INET6) {
    strcpy(family, "IPv6");
  }
#ifdef AF_LINK
  else if (sock->sa_family == AF_LINK) {
    strcpy(family, "link layer");
  }
#endif /* AF_LINK */
#ifdef AF_PACKET
  else if (sock->sa_family == AF_PACKET) {
    strcpy(family, "packet");
  }
#endif /* AF_PACKET */
  else {
    sprintf(family, "unsupported (%d)", sock->sa_family);
  }
  return family;
}

struct sockaddr *stringToAddress(char *addr, struct sockaddr_storage *sock)
{
  char mac[6][3];
  int length;
  struct addrinfo *res;
  if ((sscanf(addr, "%2[a-fA-F0-9]:%2[a-fA-F0-9]:%2[a-fA-F0-9]:%2[a-fA-F0-9]:%2[a-fA-F0-9]:%2[a-fA-F0-9]%n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], &length) == 6) && (strlen(addr) == length)) {
#ifdef AF_LINK
    struct sockaddr_dl *linkSock = (struct sockaddr_dl *)sock;
    memset(sock, 0, sizeof(struct sockaddr_dl));
#ifdef HAVE_SOCKADDR_DL_SDL_LEN
    linkSock->sdl_len = sizeof(struct sockaddr_dl);
#endif /* HAVE_SOCKADDR_DL_SDL_LEN */
    linkSock->sdl_family = AF_LINK;
    linkSock->sdl_alen = 6;
    for (int i = 0; i < linkSock->sdl_alen; i++) {
      linkSock->sdl_data[i] = (u_char)strtol(mac[i], NULL, 16);
    }
#elif defined AF_PACKET
    struct sockaddr_ll *packetSock = (struct sockaddr_ll *)sock;
    memset(sock, 0, sizeof(struct sockaddr_ll));
#ifdef HAVE_SOCKADDR_LL_SLL_LEN
    packetSock->sll_len = sizeof(struct sockaddr_ll);
#endif /* HAVE_SOCKADDR_LL_SLL_LEN */
    packetSock->sll_family = AF_PACKET;
    packetSock->sll_halen = 6;
    for (int i = 0; i < packetSock->sll_halen; i++) {
      packetSock->sll_addr[i] = (u_char)strtol(mac[i], NULL, 16);
    }
#else /* AF_LINK || AF_PACKET */
    return NULL;
#endif /* AF_LINK || AF_PACKET */
  }
  else if (getaddrinfo(addr, NULL, NULL, &res) == 0) {
    memcpy(sock, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
  }
  else {
    return NULL;
  }
  return (struct sockaddr *)sock;
}

char *addressToString(struct sockaddr *sock, char *addr)
{
  if (sock == NULL) {
    strcpy(addr, "N/A");
  }
  else if ((sock->sa_family == AF_INET) || (sock->sa_family == AF_INET6)) {
    int err;
    if ((err = getnameinfo(sock, (sock->sa_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0) {
      sprintf(addr, "error (%s)", gai_strerror(err));
    }
  }
#ifdef AF_LINK
  else if (sock->sa_family == AF_LINK) {
    struct sockaddr_dl *linkSock = (struct sockaddr_dl *)sock;
    if (linkSock->sdl_alen > 0) {
      char *mac = linkSock->sdl_data + linkSock->sdl_nlen;
      strcpy(addr, "");
      for (int i = 0; i < linkSock->sdl_alen; i++) {
        sprintf(addr, "%s%s%02x", addr, i == 0 ? "" : ":", (u_char)mac[i]);
      }
    }
    else {
      strcpy(addr, "N/A");
    }
  }
#endif /* AF_LINK */
#ifdef AF_PACKET
  else if (sock->sa_family == AF_PACKET) {
    struct sockaddr_ll *packetSock = (struct sockaddr_ll *)sock;
    if (packetSock->sll_halen > 0) {
      strcpy(addr, "");
      for (int i = 0; i < packetSock->sll_halen; i++) {
        sprintf(addr, "%s%s%02x", addr, i == 0 ? "" : ":", (u_char)packetSock->sll_addr[i]);
      }
    }
    else {
      strcpy(addr, "N/A");
    }
  }
#endif /* AF_PACKET */
  else {
    sprintf(addr, "unsupported (%d)", sock->sa_family);
  }
  return addr;
}

void usage(char *program)
{
  fprintf(stderr, "%s <interface> <destination> <port>\n", program);
}

int main(int argc, char *argv[])
{
#ifdef WIN32
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
    fprintf("Error initializing Winsock.\n");
    return 1;
  }
#endif

  if (argc != 4) {
    usage(argv[0]);
    return 2;
  }

  char *connectInterface = argv[1];
  struct sockaddr_storage connectSock;
  if (stringToAddress(argv[2], &connectSock) == NULL) {
    fprintf(stderr, "Invalid destination argument '%s'.\n", argv[2]);
    usage(argv[0]);
    return 2;
  }
  struct addrinfo *res;
  if (getaddrinfo(NULL, argv[3], NULL, &res) != 0) {
    fprintf(stderr, "Invalid port argument '%s'.\n", argv[3]);
    usage(argv[0]);
    return 2;
  }
  int connectPort;
  if (res->ai_addr->sa_family == AF_INET) {
    connectPort = ntohs(((struct sockaddr_in *)res->ai_addr)->sin_port);
  }
  else if (res->ai_addr->sa_family == AF_INET6) {
    connectPort = ntohs(((struct sockaddr_in6 *)res->ai_addr)->sin6_port);
  }
  else {
    fprintf(stderr, "Invalid port argument '%s'.\n", argv[3]);
    usage(argv[0]);
    freeaddrinfo(res);
    return 2;
  }
  freeaddrinfo(res);

  //UIPCap *uipcap = new UIPCap(&log, &error);
  struct lwipcap *lwipcap = init_lwipcap(&log,&error);
  bool validInterface = false;

  lwipcap_if *interfaces;
  //UIPCapInterface *interfaces;
  if ((interfaces = get_all_if(lwipcap)) != NULL) {
    printf("Available interfaces:\n");
    for (; interfaces != NULL; interfaces = interfaces->next) {
      printf("%s: %s%s\n", interfaces->name, interfaces->description, is_loopback(interfaces) ? " [loopback]" : "");
      for (lwipcap_addr *addresses = interfaces->getAddresses(); addresses != NULL; addresses = addresses->next) {
        char addr[NI_MAXHOST] = "";
        printf(" Type: %s\n", familyToString(addresses->addr, addr));
        printf("  Address: %s\n", addressToString(addresses->addr, addr));
        printf("  Netmask: %s\n", addressToString(addresses->netmask, addr));
        printf("  Broadcast: %s\n", addressToString(addresses->broadaddr, addr));
      }
      if (strcmp(interfaces->name, connectInterface) == 0) {
        validInterface = true;
      }
    }
  }

  if (!validInterface) {
    fprintf(stderr, "Interface '%s' not available.\n", connectInterface);
    free(lwipcap);
    return 3;
  }

  char addr[NI_MAXHOST] = "";
  printf("Destination: %s (port %d, interface %s)\n", addressToString((struct sockaddr *)&connectSock, addr), connectPort, connectInterface);

  free(lwipcap);

  return 0;
}
