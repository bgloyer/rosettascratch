cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

#project(list-monad LANGUAGES CXX)
project(scratch LANGUAGES CXX)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(${PROJECT_NAME}
amb.cpp
gamma-function.cpp
halt-and-catch-fire.cpp
horizontal-sundial-calculations.cpp
list-monad.cpp
output-for-lines-of-text.cpp
output-for-pairs-of-numbers.cpp
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

