#include "uipcap.h"

UIPCap::UIPCap(uipcapLogCallback logCallback, uipcapErrorCallback errorCallback)
  : m_allInterfaces(NULL), m_logCallback(logCallback), m_errorCallback(errorCallback)
{

}

UIPCap::~UIPCap()
{
  if (m_allInterfaces != NULL) {
    pcap_freealldevs((pcap_if_t *)m_allInterfaces);
    m_allInterfaces = NULL;
  }
}

UIPCapInterface *UIPCap::getAllInterfaces()
{
  if (m_allInterfaces != NULL) {
    pcap_freealldevs((pcap_if_t *)m_allInterfaces);
    m_allInterfaces = NULL;
  }

  char errbuf[PCAP_ERRBUF_SIZE];
  if (pcap_findalldevs((pcap_if_t **)&m_allInterfaces, errbuf) != 0) {
    uipcapErrorCallback(errbuf);
    return NULL;
  }

  return m_allInterfaces;
}

UIPCapInterface *UIPCapInterface::getNext()
{
  return (UIPCapInterface *)next;
}

char *UIPCapInterface::getName()
{
  return name;
}

char *UIPCapInterface::getDescription()
{
  return description;
}

UIPCapAddress *UIPCapInterface::getAddresses()
{
  return (UIPCapAddress *)addresses;
}

bool UIPCapInterface::isLoopback()
{
  return (flags & PCAP_IF_LOOPBACK) != 0;
}

UIPCapAddress *UIPCapAddress::getNext()
{
  return (UIPCapAddress *)next;
}

struct sockaddr *UIPCapAddress::getAaddress()
{
  return addr;
}

struct sockaddr *UIPCapAddress::getNetmask()
{
  return netmask;
}

struct sockaddr *UIPCapAddress::getBroadcast()
{
  return broadaddr;
}


