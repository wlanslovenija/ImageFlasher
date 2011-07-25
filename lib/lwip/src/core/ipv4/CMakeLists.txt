set(ipv4_srcs
  autoip.c
  icmp.c
  igmp.c
  inet.c
  inet_chksum.c
  ip.c
  ip_addr.c
  ip_frag.c
)

add_library(lwipv4 ${ipv4_srcs})
target_link_libraries(lwipv4 lwipcore)
