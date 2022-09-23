cmake_minimum_required(VERSION 3.23)
project(moe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_compile_options(
		-g -Wall -Werror -Wextra -pthread
)

add_link_options(-lpthread -lm -v -pthread)

add_library(
		moe SHARED moe/decorator.cpp moe/ArgParser.cpp moe/MoeConcept.cpp moe/STLPro.cpp
)
target_include_directories(
		moe PUBLIC moe
)

add_executable(moe_demo demo.cpp)
target_link_libraries(moe_demo moe)
