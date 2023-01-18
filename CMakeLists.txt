cmake_minimum_required(VERSION 3.23)
project(moe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_compile_options(
	-g -Wall -Werror -Wextra
)

add_link_options(-lm -v)

add_library(
	moe SHARED
	moe/moe_concept.cpp
	moe/rt_check.cpp
)
target_include_directories(
	moe PUBLIC ./moe
)

add_executable(moe_demo demo.cpp)
target_link_libraries(moe_demo moe)
