include(${QT_USE_FILE})

set(backends_SRCS
  base.cpp
)

set(backends_HDRS
  base.h
)

qt4_wrap_cpp(gui_MOCS ${gui_HDRS})

add_library(backends STATIC ${backends_SRCS} ${backends_MOCS})
