
set(core_srcs
  dns.c 
  def.c	
  mem.c
  netif.c
  raw.c 
  stats.c	
  sys.c
  tcp_in.c 
  timers.c 
  dhcp.c
  init.c
  memp.c
  pbuf.c 
  sys_arch.c
  tcp.c  
  tcp_out.c
  udp.c
)
add_subdirectory(snmp)
add_subdirectory(ipv4)
#add_subdirectory(ipv6)

add_library(lwipcore ${core_srcs})
target_link_libraries(lwipcore ${PROJECT_SOURCE_DIR}/src/netif/lwipcap)
target_link_libraries(lwipcore ${PROJECT_SOURCE_DIR}/src/api/lwipapi)

install(TARGETS lwipcore DESTINATION ${PROJECT_SOURCE_DIR}/bin)
