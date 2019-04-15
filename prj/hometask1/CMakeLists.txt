cmake_minimum_required(VERSION 3.0)

project(hometask1)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hometask1 hometask1.cpp)
target_link_libraries(hometask1 ${OpenCV_LIBS})