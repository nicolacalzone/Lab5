cmake_minimum_required(VERSION 3.0.0)
project(Lab5 VERSION 0.1.0)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Lab5 task2.cpp)

target_link_libraries(Lab5 ${OpenCV_LIBS})

