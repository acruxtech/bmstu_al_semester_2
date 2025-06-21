cmake_minimum_required(VERSION 3.10)

project(lab8)

file(GLOB_RECURSE SRC "source/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME})
