cmake_minimum_required (VERSION 2.8.11)
project (OSDL)

option(examples "EXAMPLES" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++11)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(OSDL STATIC
    ${SRC_FILES}
)
target_include_directories(OSDL PUBLIC
	include/ 
	src/ 
	src/animation
	src/raster 
	src/widget 
	src/window
)

if (EXAMPLES) 
	add_subdirectory(examples)
endif(EXAMPLES)
