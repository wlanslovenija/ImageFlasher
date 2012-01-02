set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTXML TRUE)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})


set (cmd_SRCS cmd.c unixlib.c)
add_executable(cmd ${cmd_SRCS})
add_executable(hs httpserver-netconn.c http.c unixlib.c)

add_library(tftp tftp.cpp)
add_executable(s s.c unixlib.c)
add_executable(c c.c unixlib.c)
add_executable(telnet telnet.c unixlib.c)


set (liblwip 
  lwipcap
  lwipapi
  lwipcore
  lwipv4
  lwipsnmp
  )

target_link_libraries(hs ${liblwip})
target_link_libraries(cmd ${liblwip})
target_link_libraries(s ${liblwip})
target_link_libraries(c ${liblwip})
target_link_libraries(telnet ${liblwip})
target_link_libraries(tftp ${liblwip})

install(TARGETS cmd DESTINATION ${CMAKE_BUILD_DIR}/cmd)

add_subdirectory(gui)

include(${QT_USE_FILE})

set(flasher_SRCS
  main.cpp
)

qt4_add_resources(flasher_RCS ${CMAKE_HOME_DIRECTORY}/resources/wizard.qrc)

add_executable(flasher ${flasher_RCS} ${flasher_SRCS})

target_link_libraries(flasher gui ${QT_LIBRARIES})

add_dependencies(flasher gui)
