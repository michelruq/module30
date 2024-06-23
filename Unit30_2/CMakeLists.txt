cmake_minimum_required(VERSION 3.5)

project(module30homework)

set(SRC_LIST 
          main.cpp
          threadpool/threadpool.cpp
          threadpoolqueue/threadpoolqueue.cpp)   
          
include_directories(threadpool) 
include_directories(threadpoolqueue)  
include_directories(requesthandler)    
include_directories(blockedqueue)      

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CXX_FLAGS "${CXX_FLAGS} -std=c++17 -Wall")