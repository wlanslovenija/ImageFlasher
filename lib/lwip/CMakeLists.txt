cmake_minimum_required(VERSION 2.6)
project(LwIP)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_HOME_DIRECTORY}/cmake)

include_directories (src/include test/unit)
add_subdirectory (src)

add_subdirectory (test/unit)

