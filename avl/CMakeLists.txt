add_library(avl src/avl/avl.c include/avl/avl.h)
target_include_directories(avl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)