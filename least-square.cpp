#include <iostream>
#include <ranges>

void main_ls()
{
    const int maxSquare = 1000;
    auto squareCheck = [maxSquare](int i){return 2 * i - 1 > maxSquare;};
    auto answer = std::views::iota(1) |  // {1, 2, 3, 5, ....}
      std::views::filter(squareCheck) |  // filter out the ones that are below 1000
      std::views::take(1);               // take the first one
    std::cout << answer.front() << '\n';
}
