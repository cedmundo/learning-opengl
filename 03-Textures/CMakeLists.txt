set(LECTURE_HEADERS)
set(LECTURE_SOURCES main.c)

add_executable(Textures ${LECTURE_HEADERS} ${LECTURE_SOURCES})
configure_lecture(Textures)