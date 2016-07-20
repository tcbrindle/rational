
cmake_minimum_required(VERSION 3.1)

project(tcb_rational CXX)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

include_directories(include)

add_subdirectory(example)
add_subdirectory(test)
