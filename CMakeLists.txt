cmake_minimum_required(VERSION 3.13)
project(openCV)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${temp_INCLUDE_DIRS})


add_executable(openCV main.cpp)
target_link_libraries(openCV ${OpenCV_LIBS})