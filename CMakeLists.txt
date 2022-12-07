cmake_minimum_required(VERSION 3.10) # specify the minimum version of cmake to run

project(thread) # name of the project

set(CMAKE_CXX_STANDARD 17) # which c++ version to use
set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(server main_server.cpp) # the exeexecutable name
add_executable(client main_client.cpp) # the exeexecutable name
add_executable(ipc main_ipc.cpp) # the exeexecutable name
add_executable(thread main_thread.cpp) # the exeexecutable name
add_executable(cv-server cv_server.cpp) # the exeexecutable name
add_executable(cv-client cv_client.cpp) # the exeexecutable name
add_executable(cv-msg cv_msg.cpp) # the exeexecutable name
add_executable(all-server all-server.cpp) # the exeexecutable name
add_executable(all-client all-client.cpp) # the exeexecutable name

#################
# ZeroMQ #
#################
#find_package(cppzmq)
#target_link_libraries(${PROJECT_NAME} cppzmq)

#################
# MsgPack #
#################
find_package(msgpack REQUIRED)
if (msgpack_FOUND)
    target_link_libraries(${PROJECT_NAME} msgpackc-cxx)
endif ()

#################
# OpenCV #
#################
#list(APPEND CMAKE_PREFIX_PATH "~/temp/opencv/build")
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif ()

target_link_libraries(server zmq) # link this project with the given library name
target_link_libraries(client zmq) # link this project with the given library name
target_link_libraries(ipc zmq) # link this project with the given library name
target_link_libraries(thread zmq pthread msgpackc-cxx) # link this project with the given library name
target_link_libraries(cv-server zmq pthread msgpackc-cxx ${OpenCV_LIBS}) # link this project with the given library
target_link_libraries(cv-client zmq pthread msgpackc-cxx ${OpenCV_LIBS}) # link this project with the given library name
target_link_libraries(cv-msg zmq pthread msgpackc-cxx ${OpenCV_LIBS}) # link this project with the given library name
target_link_libraries(all-server zmq pthread msgpackc-cxx ${OpenCV_LIBS}) # link this project with the given lib name
target_link_libraries(all-client zmq pthread msgpackc-cxx ${OpenCV_LIBS}) # link this project with the given lib name
