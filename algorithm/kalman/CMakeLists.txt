# Author  ： JohnnyWang
# log   :   
#=======2017.10.21.16:35(星期六)======= 创建文件

cmake_minimum_required(VERSION 2.8)
#工程名
PROJECT (project)
#调试模式
set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_CXX_FLAGS "-std=c++11")
#添加c++11标准支持


#设置全局变量
set (EXTRA_LIBS ${EXTRA_LIBS} kalmanfilter)

#注意，如果一个库要引用其他库的函数，需要将被引用的库放在后面
find_package( Sophus REQUIRED )
#find_package (OpenGL REQUIRED)

#添加头文件
include_directories( "/usr/include/eigen3" )
#include_directories(  "/home/wzq/3rd_party/Sophus"  )

#添加需要链接的库文件路径LINK_LIBRARIES
#link_libraries("/home/wzq/3rd_party/Sophus/build/libSophus.so")

#添加库文件
add_library(kalmanfilter   SHARED src/kalman/kalman.cc)

#添加可执行文件
add_executable(project src/main.cc)
#链接
target_link_libraries(project ${EXTRA_LIBS})


