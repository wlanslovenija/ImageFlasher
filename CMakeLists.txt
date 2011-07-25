project(flasher)

cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_HOME_DIRECTORY}/cmake)

                    #find_package(Qt4 4.5.0 REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

include_directories(lib/lwip/src/include)


add_subdirectory(lib)
add_subdirectory(src)
