cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(scratch LANGUAGES CXX)

add_compile_options(-Wall -Wextra -pedantic)# -Werror)

add_executable(${PROJECT_NAME}
amb.cpp
gamma-function.cpp
halt-and-catch-fire.cpp
horizontal-sundial-calculations.cpp
iterators.cpp
list-monad.cpp
least-square.cpp
output-for-lines-of-text.cpp
output-for-pairs-of-numbers.cpp
same-fringe.cpp
sum-of-cubes.cpp
tropical-algebra.cpp
writer-monad.cpp
maybe-monad.cpp
start-from-a-main-routine.cpp
pythagorean.cpp
rosettaCode.txt
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

