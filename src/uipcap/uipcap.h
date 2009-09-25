#ifndef UIPCAP_H_
#define UIPCAP_H_

#include <pcap/pcap.h>

class UIPCapAddress : pcap_addr {
public:
  UIPCapAddress *getNext();
  struct sockaddr *getAaddress();
  struct sockaddr *getNetmask();
  struct sockaddr *getBroadcast();
};

class UIPCapInterface : pcap_if_t {
public:
  UIPCapInterface *getNext();
  char *getName();
  char *getDescription();
  UIPCapAddress *getAddresses();
  bool isLoopback();
};

typedef void (*uipcapLogCallback)(const char *);
typedef void (*uipcapErrorCallback)(const char *);

class UIPCap {
public:
  UIPCap(uipcapLogCallback logCallback, uipcapErrorCallback errorCallback);
  ~UIPCap();
  UIPCapInterface *getAllInterfaces();
private:
  UIPCapInterface *m_allInterfaces;
  uipcapLogCallback m_logCallback;
  uipcapErrorCallback m_errorCallback;
};

#endif /* UIPCAP_H_ */
