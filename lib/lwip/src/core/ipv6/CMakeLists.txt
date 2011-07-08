set(ipv6_srcs
  icmp6.c
  inet6.c
  ip6.c
  ip6_addr.c
)

add_library(lwipv6 ${ipv6_srcs})
target_link_libraries(lwipv6 ${PROJECT_SOURCE_DIR}/src/lwipcore)
