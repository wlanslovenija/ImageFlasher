#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <winsock.h>
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

#include "uipcap.h"

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

struct sockaddr *stringToAddress(char *addr, struct sockaddr *sock)
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
#ifdef HAVE_SOCKADDR_LL_SLL_LEN
    packetSock->sll_len = sizeof(struct sockaddr_ll);
#endif /* HAVE_SOCKADDR_LL_SLL_LEN */
    packetSock->sll_family = AF_PACKET;
    packetSock->sll_halen = 6;
    for (int i = 0; i < packetSock->sll_halen; i++) {
      packetSock->sll_addr[i] = (u_char)strtol(mac[i], NULL, 16);
    }
#endif /* AF_LINK || AF_PACKET */
  }
  else if (getaddrinfo(addr, NULL, NULL, &res) == 0) {
    memcpy(sock, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
  }
  else {
    return NULL;
  }
  return sock;
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
  if (argc != 4) {
    usage(argv[0]);
    return 1;
  }

  char *connectInterface = argv[1];
  struct sockaddr connectSock;
  if (stringToAddress(argv[2], &connectSock) == NULL) {
    fprintf(stderr, "Invalid destination argument '%s'.\n", argv[2]);
    usage(argv[0]);
    return 1;
  }
  if (argv[3] == '\0') {
    fprintf(stderr, "Invalid port argument ''.\n");
    usage(argv[0]);
    return 1;
  }
  char *endPointer = NULL;
  long connectPort = strtol(argv[3], &endPointer, 10);
  if (*endPointer != '\0') {
    fprintf(stderr, "Invalid port argument '%s'.\n", argv[3]);
    usage(argv[0]);
    return 1;
  }
  if ((connectPort <= 0x00) || (connectPort > 0xFFFF)) {
    fprintf(stderr, "Invalid port argument '%s'.\n", argv[3]);
    usage(argv[0]);
    return 1;
  }

  UIPCap *uipcap = new UIPCap(&log, &error);

  bool validInterface = false;
  UIPCapInterface *interfaces;
  if ((interfaces = uipcap->getAllInterfaces()) != NULL) {
    printf("Available interfaces:\n");
    for (; interfaces != NULL; interfaces = interfaces->getNext()) {
      printf("%s: %s%s\n", interfaces->getName(), interfaces->getDescription(), interfaces->isLoopback() ? " [loopback]" : "");
      for (UIPCapAddress *addresses = interfaces->getAddresses(); addresses != NULL; addresses = addresses->getNext()) {
        char addr[NI_MAXHOST] = "";
        printf(" Type: %s\n", familyToString(addresses->getAaddress(), addr));
        printf("  Address: %s\n", addressToString(addresses->getAaddress(), addr));
        printf("  Netmask: %s\n", addressToString(addresses->getNetmask(), addr));
        printf("  Broadcast: %s\n", addressToString(addresses->getBroadcast(), addr));
      }
      if (strcmp(interfaces->getName(), connectInterface) == 0) {
        validInterface = true;
      }
    }
  }

  if (!validInterface) {
    fprintf(stderr, "Interface '%s' not available.\n", connectInterface);
    delete uipcap;
    return 2;
  }

  char addr[NI_MAXHOST] = "";
  printf("Destination: %s\n", addressToString(&connectSock, addr));

  delete uipcap;

  return 0;
}
