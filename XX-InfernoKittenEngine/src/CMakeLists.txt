set(LIB_SOURCES
    ike.c
    content.c
    )

set(HEADERS
    ${CONFIG_HEADER}
    ../include/ike/content.h
    )

include_directories(src)
add_library(ike STATIC ${LIB_SOURCES} ${HEADERS})
install(TARGETS ike
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/ike.h DESTINATION include)

