cmake_minimum_required(VERSION 3.9)
project(ba)

find_package(Ceres REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)
find_package(OpenCV REQUIRED)


SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

include_directories (
        ${OpenCV_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        ${Sophus_INCLUDE_DIRS}
        ${CERES_INCLUDE_DIRS}
)

add_executable(ba src/main.cpp
        )

target_link_libraries(ba
        ${CERES_LIBRARIES}
        ${OpenCV_LIBS}
        )