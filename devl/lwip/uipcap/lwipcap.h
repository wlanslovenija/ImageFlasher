#include "/home/ubuntu/libpcap/pcap/pcap.h"


typedef pcap_if_t lwipcap_if;
typedef pcap_addr lwipcap_addr;

typedef void (*lwipcap_log_callback)(const char *);
typedef void (*lwipcap_err_callback)(const char *);

struct lwipcap {
  lwipcap_if *all_ifaces;
  lwipcap_log_callback *log_callback;
  lwipcap_err_callback *err_callback;

};

/* Functions that act on struct lwipcap */
struct lwipcap* init_lwipcap(lwipcap_log_callback, lwipcap_err_callback);
void term_lwipcap(struct lwipcap*);
lwipcap_if* get_all_if(struct lwipcap*);

/* Functions that act on lwipcap_if */
char* get_if_name(lwipcap_if *);
char* get_if_descr(lwipcap_if *);
lwipcap_addr* get_if_addrs(lwipcap_if *);
lwipcap_if* get_next_if(lwipcap_if *);
is_loopback(lwipcap_if *);

/* Functions that act on lwipcap_addr */
struct sockaddr* get_netmask(lwipcap_addr *);
struct sockaddr* get_broadcast(lwipcap_addr *);
struct sockaddr* get_addr(lwipcap_addr *);
lwipcap_addr* get_next_addr(lwipcap_addr *);

