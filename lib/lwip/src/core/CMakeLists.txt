
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
  perf.c
  lwip_chksum.c
)
add_subdirectory(snmp)
add_subdirectory(ipv4)
#add_subdirectory(ipv6)

find_package(Threads)

add_library(lwipcore ${core_srcs})
target_link_libraries(lwipcore lwipcap)
target_link_libraries(lwipcore lwipapi)
target_link_libraries(lwipcore ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(lwipcore rt)

install(TARGETS lwipcore DESTINATION ${CMAKE_BUILD_DIR}/lib)
