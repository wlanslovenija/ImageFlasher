find_package(PCAP REQUIRED)

include_directories(${PCAP_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${PCAP_LIBRARIES})

set(uipcap_SRCS
  uipcap.cpp
)

add_library(uipcap STATIC ${uipcap_SRCS})
target_link_libraries(uipcap pcap)

add_executable(uipcaptest main.cpp)
target_link_libraries(uipcaptest uipcap)
