cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(list-monad LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp maybe-monad.cpp )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

