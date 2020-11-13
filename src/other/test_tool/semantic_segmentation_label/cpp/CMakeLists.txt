cmake_minimum_required(VERSION 3.9)
project(semantic_segmentation_label)
find_package (OpenCV REQUIRED)
find_package(Boost COMPONENTS system thread)

set(CMAKE_CXX_STANDARD 11)

add_executable(semantic_segmentation_label main.cpp)
target_link_libraries(semantic_segmentation_label ${BOOST_THREAD_LIBRARY} ${OpenCV_LIBS})