cmake_minimum_required(VERSION 3.0.0)
project(rpc_test)

include_directories(${RPCLIB_INCLUDE_DIR})

include_directories(3rdparty/rpclib/include/)
link_directories(3rdparty/rpclib/lib/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES main.cpp)
add_executable(rpc_test ${SOURCE_FILES})

target_link_libraries(rpc_test ${RPCLIB_LIBS} librpc.a)

add_executable(rpc_client client.cpp)

target_link_libraries(rpc_client librpc.a)
