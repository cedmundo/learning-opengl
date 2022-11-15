set(HEADERS include/common/utils.h include/common/tga.h)
set(SOURCES src/utils.c src/glad.c src/tga.c)

add_library(Common ${HEADERS} ${SOURCES})
target_include_directories(Common PUBLIC include)