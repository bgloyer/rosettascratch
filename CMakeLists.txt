cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(scratch LANGUAGES CXX)

add_compile_options(-Wall -Wextra -pedantic)# -Werror)

add_executable(${PROJECT_NAME}
amb.cpp
# church-numerals.cpp
euler-constant.cpp
first-class-functions-numbers.cpp
gamma-function.cpp
halt-and-catch-fire.cpp
horizontal-sundial-calculations.cpp
host-introspection.cpp
iterators.cpp
least-square.cpp
link-list-removal.cpp
list-monad.cpp
literals-floating-point.cpp
longest-string-challenge.cpp
maybe-monad.cpp
output-for-lines-of-text.cpp
output-for-pairs-of-numbers.cpp
# pi.cpp
printmatrix.cpp
pythagorean.cpp
# same-fringe.cpp
scratch.cpp
special-variables.cpp
start-from-a-main-routine.cpp
sum-data-type.cpp
sum-of-cubes.cpp
tropical-algebra.cpp
writer-monad.cpp
rosettaCode.txt
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

