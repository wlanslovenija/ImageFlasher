set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTXML TRUE)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(gui)
add_subdirectory(uipcap)

include(${QT_USE_FILE})

set(flasher_SRCS
  main.cpp
)

qt4_add_resources(flasher_RCS ${CMAKE_HOME_DIRECTORY}/resources/wizard.qrc)
add_executable(flasher ${flasher_RCS} ${flasher_SRCS})
target_link_libraries(flasher gui ${QT_LIBRARIES})

add_dependencies(flasher gui)
