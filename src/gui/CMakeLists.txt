include(${QT_USE_FILE})

set(gui_SRCS
  wizard.cpp
)

set(gui_HDRS
  wizard.h
)

set(gui_UIS
  wizard.ui
)

qt4_wrap_cpp(gui_MOCS ${gui_HDRS})
qt4_wrap_ui(gui_UI_SRCS ${gui_UIS})

add_library(gui STATIC ${gui_SRCS} ${gui_UI_SRCS} ${gui_MOCS})
