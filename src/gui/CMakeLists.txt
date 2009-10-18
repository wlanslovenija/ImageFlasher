include(${QT_USE_FILE})

set(gui_SRCS
  wizard.cpp
  filechooser.cpp
  steps/welcome.cpp
  steps/instructions.cpp
  steps/selection.cpp
  steps/files.cpp
  steps/progress.cpp
)

set(gui_HDRS
  wizard.h
  filechooser.h
  steps/welcome.h
  steps/instructions.h
  steps/selection.h
  steps/files.h
  steps/progress.h
)

set(gui_UIS
  wizard.ui
  steps/welcome.ui
  steps/instructions.ui
)

qt4_wrap_cpp(gui_MOCS ${gui_HDRS})
qt4_wrap_ui(gui_UI_SRCS ${gui_UIS})

add_library(gui STATIC ${gui_SRCS} ${gui_UI_SRCS} ${gui_MOCS})
