cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(list-monad LANGUAGES CXX)

message(${CMAKE_CXX_FLAGS_RELEASE})
#message(${CMAKE_CXX_FLAGS})

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp maybe-monad.cpp faulhabers-triangle.cpp)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

