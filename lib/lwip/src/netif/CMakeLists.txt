
set(lwipcap_srcs
  etharp.c
  ethernetif.c
  pcapif.c
  lwipcap.c
)

find_package(PCAP)

add_library(lwipcap ${lwipcap_srcs})
target_link_libraries(lwipcap pcap)

install(TARGETS lwipcap DESTINATION ${CMAKE_BUILD_DIR}/lib/lwipcap)

add_dependencies(lwipcap PCAP)
