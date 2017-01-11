include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(OpenTCG main.cpp)

target_link_libraries(OpenTCG ${GTKMM_LIBRARIES})
