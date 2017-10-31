# Author  ： JohnnyWang
# log   :   
#=======2017.10.24.09:41(星期二)======= 创建文件

cmake_minimum_required(VERSION 2.8)
#工程名
PROJECT (project)
#设置全局变量
#set (EXTRA_LIBS ${EXTRA_LIBS} state context)
#注意，如果一个库要引用其他库的函数，需要将被引用的库放在后面
find_package(Boost COMPONENTS filesystem regex REQUIRED)   # 最好是加上REQUIRED，否则找不到某些库也不会报错，链接会出问题

#添加库文件搜索路径  
LINK_DIRECTORIES(/usr/local/lib)  
#添加库文件
#add_library(state     SHARED src/state.cpp)
#add_library(context   SHARED src/context.cpp)
#添加可执行文件
add_executable(project src/main.cpp)
#链接
target_link_libraries(project boost_thread boost_system)#also add boost_system can work
