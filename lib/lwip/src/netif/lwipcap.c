#include "lwipcap.h"

char* get_if_name(lwipcap_if_t* lwipcapif)
{
  return lwipcapif->name;
}

char* get_if_descr(lwipcap_if_t* lwipcapif)
{
  return lwipcapif->description;
}

lwipcap_if_t* get_next_if(lwipcap_if_t* lwipcapif)
{
  return (lwipcap_if_t*) lwipcapif->next;
}

bool is_loopback(lwipcap_if_t* interface)
{
  return (interface->flags & PCAP_IF_LOOPBACK) != 0 ;
}

lwipcap_addr_t* get_next_addr(lwipcap_addr_t* lwipcapaddr)
{
  return lwipcapaddr->next;
}

struct sockaddr* get_addr(lwipcap_addr_t* lwipaddr)
{
  return lwipaddr->addr;
}

struct sockaddr* get_netmask(lwipcap_addr_t* lwipaddr)
{
  return lwipaddr->netmask;
}

struct sockaddr* get_broadcast(lwipcap_addr_t* lwipaddr)
{
  return lwipaddr->broadaddr;
}

lwipcap_if_t* get_all_if(struct lwipcap* lwipcap)
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

lwipcap_addr_t* get_if_addrs(lwipcap_if_t* lwipcapif) 
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


