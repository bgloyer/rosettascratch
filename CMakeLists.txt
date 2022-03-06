cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(scratch LANGUAGES CXX)

add_compile_options(-Wall -Wextra -pedantic)# -Werror)

add_executable(${PROJECT_NAME}
amb.cpp
first-class-functions-numbers.cpp
gamma-function.cpp
halt-and-catch-fire.cpp
horizontal-sundial-calculations.cpp
iterators.cpp
least-square.cpp
list-monad.cpp
literals-floating-point.cpp
output-for-lines-of-text.cpp
output-for-pairs-of-numbers.cpp
printmatrix.cpp
same-fringe.cpp
sum-data-type.cpp
sum-of-cubes.cpp
tropical-algebra.cpp
writer-monad.cpp
maybe-monad.cpp
start-from-a-main-routine.cpp
pi.cpp
pythagorean.cpp
rosettaCode.txt
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

