project(Lab5)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Task1 task1.cpp)
add_executable(Task2 task2.cpp)
add_executable(Task3 task3.cpp)

target_link_libraries(Task1 ${OpenCV_LIBS})
target_link_libraries(Task2 ${OpenCV_LIBS})
target_link_libraries(Task3 ${OpenCV_LIBS})

