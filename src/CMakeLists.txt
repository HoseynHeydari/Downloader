cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT "/usr/local/Cellar/boost/1.74.0")
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

set(SOURCE main.cpp Configure.cpp)

set(PROTO
	protobuf/InputOutput.proto
	protobuf/Writer.proto
	)

# TODO: create find_package macro

find_package(Protobuf REQUIRED)
if(Protobuf_FOUND)
	include_directories(${Protobuf_INCLUDE_DIRS})
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
	protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO})
else()
	message("====================")
	message(" protobuf not found.")
	message("====================")
endif()

find_package(Boost 1.74.0 COMPONENTS thread regex system)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
else()
	message("====================")
	message("  boost not found.  ")
	message("====================")
endif()

add_executable(${PROJECT_NAME}
	${SOURCE}
	${PROTO_SRCS}
	${PROTO_HDRS}
	)

target_link_libraries(${PROJECT_NAME}
	${Boost_THREAD_LIBRARY}
	${Boost_REGEX_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Protobuf_LIBRARIES}
	)
