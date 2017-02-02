cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project (OpenTCG)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(LIBXML++ REQUIRED libxml++-2.6)

add_subdirectory(include)
add_subdirectory(src)
