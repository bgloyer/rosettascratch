#include <iostream>
#include <boost/hana.hpp>
#include <boost/hana/experimental/printable.hpp>
#include <string_view>

using namespace std;
namespace hana = boost::hana;

constexpr auto Folder(auto f)
{
  return [f](auto a, auto b)
  {
    bool isValid = hana::unpack(a, f);
    return isValid ? a : b;
  };
}

constexpr auto Folder2(auto f)
{
  return [f](auto a, auto b)
  {
    bool isValid = f(a);
    return isValid ? a : b;
  };
}

constexpr auto Amb(auto f, auto params)
{
  
}

int main()
{
  hana::tuple x{1, 2, 3};
  hana::tuple y{7, 6, 4, 5};

  auto cross = hana::cartesian_product(hana::tuple{x, y});

  constexpr auto xxxx = [](int x, int y){return x * y == 8;};

  constexpr auto foldOp = Folder(xxxx);
  auto result = hana::fold_right(cross, foldOp); 

  cout << "\nx = " << hana::experimental::print(x);
  cout << "\ny = " << hana::experimental::print(y);
  cout << "\nx * y == 8: " << hana::experimental::print(result);

  auto words1 = hana::make_tuple("the"sv, "that"sv, "a"sv);
  auto words2 = hana::make_tuple("frog"sv, "elephant"sv, "thing"sv);
  auto words3 = hana::make_tuple("walked"sv, "treaded"sv, "grows"sv);
  auto words4 = hana::make_tuple("slowly"sv, "quickly"sv);

  auto wordsCross = hana::cartesian_product(hana::tuple{words1, words2, words3, words4});

  constexpr auto matches = [](const auto t)
  {
    auto first = hana::drop_back(t);
    auto last = hana::drop_front(t);
    auto adjacent = hana::zip(first, last);
    auto bools = hana::transform(adjacent, [](auto t)
    {
      return t[hana::size_c<0>].back() == t[hana::size_c<1>].front();
    });
    auto match = hana::fold_right(bools, [](bool b1, bool b2)
    {
      return b1 && b2;
    });
    return match;
  };

  constexpr auto foldWordsOp = Folder2(matches);
  auto wordResult = hana::fold_right(wordsCross, foldWordsOp);
  cout << "\n\nWords 1: " << hana::experimental::print(words1);
  cout << "\nWords 2: " << hana::experimental::print(words2);
  cout << "\nWords 3: " << hana::experimental::print(words3);
  cout << "\nWords 4: " << hana::experimental::print(words4);
  cout << "\nSolution: " << hana::experimental::print(wordResult) << "\n";
}
