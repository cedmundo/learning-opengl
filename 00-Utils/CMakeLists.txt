set(HEADERS include/lofw/utils.h)
set(SOURCES src/utils.c src/glad.c)

add_library(LOUtils ${HEADERS} ${SOURCES})
target_include_directories(LOUtils PUBLIC include)