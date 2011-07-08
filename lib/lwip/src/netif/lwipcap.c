#include "lwipcap.h"

char* get_if_name(lwipcap_if* lwipcapif)
{
  return lwipcapif->name;
}

char* get_if_descr(lwipcap_if* lwipcapif)
{
  return lwipcapif->description;
}

lwipcap_if* get_next_if(lwipcap_if* lwipcapif)
{
  return (lwipcap_if*) lwipcapif->next;
}

bool is_loopback(lwipcap_if* interface)
{
  return (interface->flags & PCAP_IF_LOOPBACK) != 0 ;
}

lwipcap_addr* get_next_addr(lwipcap_addr* lwipcapaddr)
{
  return lwipcapaddr->next;
}

struct sockaddr* get_addr(lwipcap_addr* lwipaddr)
{
  return lwipaddr->addr;
}

struct sockaddr* get_netmask(lwipcap_addr* lwipaddr)
{
  return lwipaddr->netmask;
}

struct sockaddr* get_broadcast(lwipcap_addr* lwipaddr)
{
  return lwipaddr->broadaddr;
}

lwipcap_if* get_all_if(struct lwipcap* lwipcap)
{
  if (lwipcap->all_ifaces != NULL) {
    pcap_freealldevs((pcap_if_t*)lwipcap->all_ifaces);
    lwipcap->all_ifaces = NULL;
  }

  char errbuf[PCAP_ERRBUF_SIZE];
  if (pcap_findalldevs((pcap_if_t **)&(lwipcap->all_ifaces), errbuf) != 0) {
    lwipcap->err_callback(errbuf);
    return NULL;
  }

  return lwipcap->all_ifaces;
}

lwipcap_addr* get_if_addrs(lwipcap_if* lwipcapif) 
{
  return lwipcapif->addresses;
}

struct lwipcap* init_lwipcap(lwipcap_log_callback log_callback, lwipcap_err_callback err_callback)
{
  struct lwipcap* lwipcap = (struct lwipcap*) safe_malloc(sizeof(struct lwipcap));
  lwipcap->log_callback = log_callback;
  lwipcap->err_callback = err_callback;
  lwipcap->all_ifaces = NULL;

  return lwipcap;
}

void term_lwipcap(struct lwipcap* lwipcap)
{
  if(lwipcap->all_ifaces != NULL)
    pcap_freealldevs((pcap_if_t*)lwipcap->all_ifaces);
  lwipcap->all_ifaces = NULL;  
  return;
}


