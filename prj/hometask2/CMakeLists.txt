cmake_minimum_required(VERSION 3.0)

project(hometask2)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hometask2 hometask2.cpp)
target_link_libraries(hometask2 ${OpenCV_LIBS})