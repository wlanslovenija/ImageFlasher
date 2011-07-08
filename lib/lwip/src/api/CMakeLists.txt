
set(api_srcs
  api_lib.c
  api_msg.c
  err.c 
  netbuf.c
  netdb.c
  netifapi.c 
  sockets.c  
  tcpip.c
)

add_library(lwipapi ${api_srcs})
target_link_libraries(lwipapi 
  ${PROJECT_SOURCE_DIR}/src/netif/lwipcap 
)

install(TARGETS lwipapi DESTINATION ${PROJECT_SOURCE_DIR}/bin)
