# 作者  ： JohnnyWang
# log   :   
#=======2017.08.16.16:35(星期三)======= 创建文件

cmake_minimum_required(VERSION 2.8)
PROJECT (state_pattern)
set(CMAKE_CXX_FLAGS "-std=c++14")
add_executable(state_pattern src/main.cpp src/context.hpp src/state.h src/state.cpp)

