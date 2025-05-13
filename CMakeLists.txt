cmake_minimum_required(VERSION 3.10)

project(hw1)

file(GLOB_RECURSE SRC "source/*.cpp")
include_directories(include)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME})
