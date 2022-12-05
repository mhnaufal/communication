cmake_minimum_required(VERSION 3.10) # specify the minimum version of cmake to run

project(thread) # name of the project

set(CMAKE_CXX_STANDARD 17) # which c++ version to use
set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(server main_server.cpp) # the exeexecutable name
add_executable(client main_client.cpp) # the exeexecutable name

target_link_libraries(server zmq) # link this project with the given library name
target_link_libraries(client zmq) # link this project with the given library name

#################
# zeromq #
#################
#find_package(cppzmq)
#target_link_libraries(${PROJECT_NAME} cppzmq)