cmake_minimum_required(VERSION 3.0)

project(downloader)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

set(PACKAGE_TESTS PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)

# option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
	enable_testing()
	include(GoogleTest)
	add_subdirectory(test)
endif()