set (SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
	)

include_directories(${GTKMM_INCLUDE_DIRS} ../include ${LIBXML++_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS} ${LIBXML++_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

add_subdirectory(util)
add_subdirectory(gui)
add_subdirectory(game)

add_executable(OpenTCG ${SOURCE} ${HEADERS})

target_link_libraries(OpenTCG ${GTKMM_LIBRARIES} ${LIBXML++_LIBRARIES})

