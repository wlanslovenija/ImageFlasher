
set(lwipcap_srcs
  etharp.c
  ethernetif.c
  pcapif.c
  lwipcap.c
)

find_package(PCAP)

add_library(lwipcap ${lwipcap_srcs})
install(TARGETS lwipcap DESTINATION ${PROJECT_SOURCE_DIR}/bin)
add_dependencies(lwipcap PCAP)
