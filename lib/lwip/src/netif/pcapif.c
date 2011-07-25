/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "lwip/opt.h"


#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "netif/ppp_oe.h"
#include <pcap.h>
#include <pcap-int.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>

#include "lwipcap.h"
/* Define those to better describe your network interface. */
#define IFNAME0 'p'
#define IFNAME1 'c'
#define SNAPLEN 65535

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct pcapif {
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */

  char name[10];
  u8_t *pref_if;
  u8_t errbuf[PCAP_ERRBUF_SIZE];  // Error buffer to store pcap related errors
  pcap_t *pc_descr;         // Pcap descriptor of the interface
  u8_t *iface;
  struct pcap_pkthdr* pkthdr;
  u8_t *payload;
  struct bpf_program bpf_prog;

  // Add pcap related attributes here

};

/* Forward declarations. */
static void  pcapif_input(struct netif *netif);
static void  pcapif_loop_init(struct netif *netif);

void checkfunc(u_char *, const struct pcap_pkthdr*, const u_char *);

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void
low_level_init(struct netif *netif)
{
  struct pcapif *pcapif = netif->state;

  // Remove this later
  
  pcapif->pref_if = malloc(strlen("vboxnet0")+1);
  strncpy(pcapif->pref_if, "vboxnet0", strlen("vboxnet0")+1);
  if(pcapif->pref_if == NULL){
    pcapif->iface = pcap_lookupdev(pcapif->errbuf);
    if(pcapif->iface == NULL)
      return;
  }else{
    pcapif->iface = pcapif->pref_if;
  }

  pcapif->pc_descr = pcap_open_live(pcapif->iface,SNAPLEN,0,100,pcapif->errbuf);

  if(pcapif->pc_descr == (pcap_t *)NULL){
    printf(" pcap_open_live : %s\n", pcapif->errbuf);
    return;
  }
  
  /*lwipcap_addr_t *lwipaddr = get_if_addrs((lwipcap_if_t*) pcapif->pc_descr);

  struct sockaddr *temp = get_addr(lwipaddr);
 
  (netif->ip_addr).addr = htonl(temp->sa_data);

  (netif->netmask).addr = htonl(get_netmask(lwipaddr));
 */ 

  init_ll(netif);

  sys_thread_new("pcap_loop_thread", pcapif_loop_init, netif, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
  
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP | NETIF_FLAG_UP;
 
  /* Figure out what sort of a pcap filter to set here */
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  struct pcapif *pcapif = netif->state;
  struct pbuf *q;

  // Whoa! what is this, huh? initiate transfer();
  
#if ETH_PAD_SIZE
  pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

  for(q = p; q != NULL; q = q->next) {
    /* Send the data from the pbuf to the interface, one pbuf at a
       time. The size of the data in each pbuf is kept in the ->len
       variable. */
    printf(" %c %c \n",netif->name[0], netif->name[1]);
    int ret = pcap_inject(pcapif->pc_descr,q->payload,q->len);
//DEBUG 
      printf("pcapinject : %d\n",ret);
    if(ret == -1)
      pcap_perror(pcapif->pc_descr,"pcap_inject");
  }

  // Whoa!! what is this?? ?signal that packet should be sent();

#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
  
  LINK_STATS_INC(link.xmit);

  return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif)
{
  struct pcapif *pcapif = netif->state;
  struct pbuf *p, *q;
  u16_t len;

  /* Obtain the size of the packet and put it into the "len"
     variable. */
  len = pcapif->pkthdr->len;

#if ETH_PAD_SIZE
  len += ETH_PAD_SIZE /* allow room for Ethernet padding */
#endif

  /* We allocate a pbuf chain of pbufs from the pool. */
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  
  if (p != NULL) {

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    /* We iterate over the pbuf chain until we have read the entire
     * packet into the pbuf. */
    for(q = p; q != NULL; q = q->next) {
      /* Read enough bytes to fill this pbuf in the chain. The
       * available data in the pbuf is given by the q->len
       * variable.
       * This does not necessarily have to be a memcpy, you can also preallocate
       * pbufs for a DMA-enabled MAC and after receiving truncate it to the
       * actually received size. In this case, ensure the tot_len member of the
       * pbuf is the sum of the chained pbuf len members.
       */
      memcpy(q->payload,pcapif->payload,q->len);
      pcapif->payload += q->len;
      
    }
    //acknowledge that packet has been read();

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.recv);
  } else {
    return NULL;
    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
  }

  return p;  
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
static void
pcapif_input(struct netif *netif)
{
  struct pcapif *pcapif;
  struct eth_hdr *ethhdr;
  struct pbuf *p;

  pcapif = netif->state;

  /* move received packet into a new pbuf */
  p = low_level_input(netif);
  /* no packet could be read, silently ignore this */
  if (p == NULL) return;
  /* points to packet payload, which starts with an Ethernet header */
  ethhdr = p->payload;

  switch (htons(ethhdr->type)) {
  /* IP or ARP packet? */
  case ETHTYPE_IP:
  case ETHTYPE_ARP:
#if PPPOE_SUPPORT
  /* PPPoE packet? */
  case ETHTYPE_PPPOEDISC:
  case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif)!=ERR_OK)
     { LWIP_DEBUGF(NETIF_DEBUG, ("pcapif_input: IP input error\n"));
       pbuf_free(p);
       p = NULL;
     }
    break;

  default:
    pbuf_free(p);
    p = NULL;
    break;
  }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
pcapif_init(struct netif *netif)
{
  struct pcapif *pcapif;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
    
  pcapif = mem_malloc(sizeof(struct pcapif));
  if (pcapif == NULL) {
    LWIP_DEBUGF(NETIF_DEBUG, ("pcapif_init: out of memory\n"));
    return ERR_MEM;
  }

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */

  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

  netif->state = pcapif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;

  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */

  /* Currently we assume ethernet */

#if NO_SYS==1
  netif->input=tcpip_input;
#else
  netif->input=ethernet_input;
#endif
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;
  
  pcapif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);
  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}


void init_ll(struct netif *netif)
{
  /* set MAC Address
   * set MTU
   * set netif->hwaddr_len
   */

  struct ifconf ifc;
  struct ifreq *IFR = &(ifc.ifc_req);
  int i,sock;
  char buf[1024];
  struct pcapif *pcapif = netif->state;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  ifc.ifc_len = sizeof(buf);
  ifc.ifc_buf = buf;

  ioctl(sock, SIOCGIFCONF, &ifc);

  for(i=0; i<ifc.ifc_len/sizeof(struct ifreq); i++){

    if(strcmp(IFR[i].ifr_name, pcapif->name) == 0){
      ioctl(sock, SIOCGIFHWADDR, &(IFR[i]));
      memcpy(netif->hwaddr, &(IFR[i].ifr_hwaddr.sa_data), ETHARP_HWADDR_LEN);
      netif->hwaddr_len = ETHARP_HWADDR_LEN;

      ioctl(sock, SIOCGIFMTU, &(ifc.ifc_req[i]));
      netif->mtu = IFR[i].ifr_mtu;
    }
  }

  return;
}


void pcapif_loop_init(struct netif *netif)
{
  printf("\n\n\npcap_loop_init : starting\n\n\n");

  struct pcapif *pcapif = netif->state;

  pcap_compile(pcapif->pc_descr, &(pcapif->bpf_prog), "", 0, netif->netmask.addr);

  pcap_setfilter(pcapif->pc_descr, &(pcapif->bpf_prog));

  if(pcap_loop(pcapif->pc_descr, -1, checkfunc, (u_char *)netif) == -1){
    printf("pcap_loop : error\n");
  }

}

void checkfunc(u_char *pcif, const struct pcap_pkthdr *hdr, const u_char * pkt)
{
  printf(" Recieved a packet\n");
  struct netif *netif = pcif;
  struct pbuf *pktbuf = pbuf_alloc(PBUF_LINK, hdr->len,PBUF_RAM);
  pktbuf->payload = pkt;
  netif->input(pktbuf, netif);
}
