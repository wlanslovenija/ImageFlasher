set(${test_srcs}
  test_tcp.c
  test_udp.c
  test_tcp_oos.c
  test_mem.c
  test_etharp.c
  tcp_helper.c
  lwip_unittests.c
)

add_executable(unittest lwip_unittests.c)
target_link_libraries(unittest ${PROJECT_SOURCE_DIR}/src/api/lwipapi)

install(TARGETS unittest DESTINATION ${PROJECT_SOURCE_DIR}/bin/unittest)
