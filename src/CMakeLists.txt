set (cmd_SRCS cmd.c unixlib.c)
add_executable(cmd ${cmd_SRCS})
add_executable(hs httpserver-netconn.c http.c unixlib.c)

add_library(tlib tftp_server.cpp unixlib.c)
add_executable(s s.c unixlib.c)
add_executable(c c.c unixlib.c)

set (liblwip 
  lwipcap
  lwipapi
  lwipcore
  lwipv4
  lwipsnmp
  )

target_link_libraries(tlib ${liblwip})
target_link_libraries(hs ${liblwip})
target_link_libraries(cmd ${liblwip})
target_link_libraries(s ${liblwip})
target_link_libraries(c ${liblwip})

install(TARGETS cmd DESTINATION ${CMAKE_BUILD_DIR}/cmd)


