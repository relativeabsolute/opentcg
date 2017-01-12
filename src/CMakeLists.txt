set (SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
	)

include_directories(${GTKMM_INCLUDE_DIRS} ../include)
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

add_subdirectory(gui)

add_executable(OpenTCG ${SOURCE} ${HEADERS})

target_link_libraries(OpenTCG ${GTKMM_LIBRARIES})

