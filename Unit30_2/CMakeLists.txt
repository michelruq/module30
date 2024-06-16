cmake_minimum_required(VERSION 3.5)

project(module30homework)

set(SRC_LIST 
          main.cpp
          threadpool/threadpool.cpp
          requesthandler/requesthandler.cpp)   
          
include_directories(threadpool)  
include_directories(requesthandler)        

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CXX_FLAGS "${CXX_FLAGS} -std=c++17 -Wall")