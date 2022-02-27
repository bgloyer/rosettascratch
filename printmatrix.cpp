#include <concepts>
#include <iostream>
#include <stdio.h>

// Print each element of a matrix according to a predicate.  It
// will print a '1' if the predicate function is true, otherwise '0'. 
void PrintMatrix(std::predicate<int, int, int> auto f, int size)
{
  for(int y = 0; y < size; y++)
  {
    for(int x = 0; x < size; x++)
    {
      std::cout << " " << f(x, y, size);
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}


void main_pm()
{
  // a lambda to create diagonals
  auto diagonals = [](int x, int y, int size)
  {
    return x == y || ((size - x - 1) == y);
  };

  // a lambda to create a mosaic
  auto mosaic = [](int x, int y, [[maybe_unused]]int size)
  {
    return (x + y) % 2 == 0;
  };

  // a lambda to show the sides
  auto fourSides = [](int x, int y, int size)
  {
    return x == 0 || (y == 0) || (x == size - 1) || (y == size - 1);
  };

  PrintMatrix(diagonals, 8);
  PrintMatrix(diagonals, 9);
  PrintMatrix(mosaic, 8);
  PrintMatrix(mosaic, 9);
  PrintMatrix(fourSides, 8);
  PrintMatrix(fourSides, 9);

  printf("\33[2J");
}
