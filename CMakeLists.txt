# ------------------------------------------------------------------------------------------
# TOPLEVEL CMakeLists.txt
# ------------------------------------------------------------------------------------------
project(flasher)

cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 4.5.0 REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(src)

# ------------------------------------------------------------------------------------------
# src/CMakeLists.txt
# ------------------------------------------------------------------------------------------
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTXML TRUE)

include(${QT_USE_FILE})

set(flasher_SRCS
  src/main.cpp
  src/gui/wizard.cpp
)

set(flasher_HDRS
  src/gui/wizard.h
)

set (flasher_UIS
  src/gui/wizard.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES}${CMAKE_CURRENT_SOURCE_DIR} )

qt4_wrap_cpp(flasher_MOCS ${flasher_HDRS})
qt4_wrap_ui(flasher_UI_SRCS ${flasher_UIS})
qt4_add_resources(flasher_RCS resources/wizard.qrc)

#add_executable(flasher WIN32 ${flasher_RCS} ${flasher_SRCS} ${flasher_UI_SRCS} ${flasher_MOCS})
add_executable(flasher ${flasher_RCS} ${flasher_SRCS} ${flasher_UI_SRCS} ${flasher_MOCS})

target_link_libraries(flasher ${QT_LIBRARIES})

add_dependencies(flasher core widgets dialogs)
