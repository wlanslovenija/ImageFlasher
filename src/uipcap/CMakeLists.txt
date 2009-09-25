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

INCLUDE(CheckStructHasMember)

set(HAVE_SOCKADDR_DL_SDL_LEN_HDRS
  sys/types.h
  net/if_dl.h
)

set(HAVE_SOCKADDR_LL_SLL_LEN_HDRS
  sys/types.h
  netpacket/packet.h
)

CHECK_STRUCT_HAS_MEMBER("struct sockaddr_dl" sdl_len "${HAVE_SOCKADDR_DL_SDL_LEN_HDRS}" HAVE_SOCKADDR_DL_SDL_LEN)
CHECK_STRUCT_HAS_MEMBER("struct sockaddr_ll" sll_len "${HAVE_SOCKADDR_LL_SLL_LEN_HDRS}" HAVE_SOCKADDR_LL_SLL_LEN)

add_library(uipcap STATIC ${uipcap_SRCS} ${uipcap_HDRS} ${uip_SRCS})
target_link_libraries(uipcap pcap)

add_executable(uipcaptest main.cpp)
target_link_libraries(uipcaptest uipcap)
