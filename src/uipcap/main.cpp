#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <net/if_dl.h>

#include "uipcap.h"

void error(const char *errstr) {
  fprintf(stderr, "Error: %s\n", errstr);
}

void familyToString(struct sockaddr *sock, char *family) {
  if (sock == NULL) {
    strcpy(family, "N/A");
  }
  else if (sock->sa_family == AF_INET) {
    strcpy(family, "IPv4");
  }
  else if (sock->sa_family == AF_INET6) {
    strcpy(family, "IPv6");
  }
  else if (sock->sa_family == AF_LINK) {
    strcpy(family, "link layer");
  }
  else {
    strcpy(family, "unsupported");
  }
}

void addressToString(struct sockaddr *sock, char *addr) {
  if (sock == NULL) {
    strcpy(addr, "N/A");
  }
  else if ((sock->sa_family == AF_INET) || (sock->sa_family == AF_INET6)) {
    int err;
    if ((err = getnameinfo(sock, sizeof(struct sockaddr), addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0) {
      strcpy(addr, "error");
    }
  }
  else if (sock->sa_family == AF_LINK) {
    struct sockaddr_dl *macSock = (struct sockaddr_dl *)sock;
    if (macSock->sdl_alen > 0) {
      char *mac = macSock->sdl_data + macSock->sdl_nlen;
      strcpy(addr, "");
      for (int i = 0; i < macSock->sdl_alen; i++) {
        sprintf(addr, "%s%s%02x", addr, i == 0 ? "" : ":", (u_char)mac[i]);
      }
    }
    else {
      strcpy(addr, "N/A");
    }
  }
  else {
    strcpy(addr, "unsupported");
  }
}

int main(int argc, char *argv[]) {
  UIPCap *uipcap = new UIPCap(&error);

  UIPCapInterface *interfaces;
  if ((interfaces = uipcap->getAllInterfaces()) != NULL) {
    printf("Available interfaces:\n");
    for (; interfaces != NULL; interfaces = interfaces->getNext()) {
      printf("%s: %s%s\n", interfaces->getName(), interfaces->getDescription(), interfaces->isLoopback() ? " [loopback]" : "");
      for (UIPCapAddress *addresses = interfaces->getAddresses(); addresses != NULL; addresses = addresses->getNext()) {
        char addr[NI_MAXHOST] = "";
        struct sockaddr *sock = NULL;

        sock = addresses->getAaddress();

        familyToString(sock, addr);
        printf(" Type: %s\n", addr);

        addressToString(sock, addr);
        printf("  Address: %s\n", addr);

        sock = addresses->getNetmask();
        addressToString(sock, addr);
        printf("  Netmask: %s\n", addr);

        sock = addresses->getBroadcast();
        addressToString(sock, addr);
        printf("  Broadcast: %s\n", addr);
      }
    }
  }

  delete uipcap;
}
