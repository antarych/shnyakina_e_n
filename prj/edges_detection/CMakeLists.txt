cmake_minimum_required(VERSION 3.0)

project(edges_detection)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(edges_detection edges_detection.cpp)
target_link_libraries(edges_detection ${OpenCV_LIBS})