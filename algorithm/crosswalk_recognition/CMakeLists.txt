cmake_minimum_required(VERSION 3.10)
project(crosswalk_recognition)
find_package(OpenCV QUIET)

set(CMAKE_CXX_STANDARD 11)
include_directories("usr/include/eigen3")

add_executable(crosswalk_recognition main.cpp)
target_link_libraries(crosswalk_recognition
        ${OpenCV_LIBS}
        )