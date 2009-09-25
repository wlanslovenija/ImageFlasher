find_package(PCAP REQUIRED)

include_directories(${PCAP_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${PCAP_LIBRARIES})

set(uip_SRCS
  ${CMAKE_HOME_DIRECTORY}/libs/uip/uip/uip.c
  ${CMAKE_HOME_DIRECTORY}/libs/uip/uip/uip_arp.c
)

set(uipcap_SRCS
  uipcap.cpp
)

set(uipcap_HDRS
  uipcap.h
  uip-conf.h
)

add_library(uipcap STATIC ${uipcap_SRCS} ${uipcap_HDRS} ${uip_SRCS})
target_link_libraries(uipcap pcap)

add_executable(uipcaptest main.cpp)
target_link_libraries(uipcaptest uipcap)
