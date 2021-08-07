cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(list-monad LANGUAGES CXX)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(list-monad LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp
gamma-function.cpp
sum-of-cubes.cpp
tropical-algebra.cpp
writer-monad.cpp
maybe-monad.cpp
start-from-a-main-routine.cpp
pythagorean.cpp
coreguidelines.cpp
rosettaCode.txt
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

