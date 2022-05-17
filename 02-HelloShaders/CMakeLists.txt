set(LECTURE_HEADERS)
set(LECTURE_SOURCES main.c)

add_executable(HelloShaders ${LECTURE_HEADERS} ${LECTURE_SOURCES})
configure_lecture(HelloShaders)