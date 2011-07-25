#include <pcap.h>
typedef enum{FALSE=0,TRUE=1} bool;

typedef pcap_if_t lwipcap_if_t;
typedef pcap_addr_t lwipcap_addr_t;

typedef void (*lwipcap_log_callback)(const char *);
typedef void (*lwipcap_err_callback)(const char *);

struct lwipcap {
  lwipcap_if_t *all_ifaces;
  lwipcap_log_callback log_callback;
  lwipcap_err_callback err_callback;

};

/* Functions that act on struct lwipcap */
struct lwipcap* init_lwipcap(lwipcap_log_callback, lwipcap_err_callback);
void term_lwipcap(struct lwipcap*);
lwipcap_if_t* get_all_if(struct lwipcap*);

/* Functions that act on lwipcap_if */
char* get_if_name(lwipcap_if_t*);
char* get_if_descr(lwipcap_if_t*);
lwipcap_addr_t* get_if_addrs(lwipcap_if_t*);
lwipcap_if_t* get_next_if(lwipcap_if_t*);
bool is_loopback(lwipcap_if_t*);

/* Functions that act on lwipcap_addr */
struct sockaddr* get_netmask(lwipcap_addr_t*);
struct sockaddr* get_broadcast(lwipcap_addr_t*);
struct sockaddr* get_addr(lwipcap_addr_t*);
lwipcap_addr_t* get_next_addr(lwipcap_addr_t*);

