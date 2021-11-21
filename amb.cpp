#include <iostream>
#include <boost/hana.hpp>

using namespace std;
namespace hana = boost::hana;

void pr(int a, int b)
{
  cout << "ab" << a << ", " << b << "\n";
}

// //auto Check(auto x)
// constexpr auto Check(hana::tuple<int, int> x)
// {
//   hana::unpack(x, pr);
//   return hana::tuple<decltype(x)>{x};
//  // return x;
// }

constexpr auto MakeCheck(auto f)
{
  return [f](auto x) -> decltype(auto)
  {
    bool isValid = hana::unpack(x, f);
    if (isValid) return hana::tuple<decltype(x)>{x};
//    else return hana::tuple<hana::empty<decltype(x)>>{x};
//    else return hana::empty<decltype(hana::tuple<decltype(x)>)();
    else return hana::empty<hana::tuple<hana::tuple<int, int>>>();
//    else return hana::tuple<hana::empty<hana::tuple<int, int>>>();
  };
}

int main()
{
  int tmp = 9;

  hana::tuple x{1, 2, 3, tmp};
  hana::tuple y{7, 6, 4, 5};

  hana::tuple tuples{x, y};

  auto cross = hana::cartesian_product(tuples);

  //hana::for_each (cross, [](auto x){hana::unpack(x, pr);});

  constexpr auto xxxx = [](int x, int y){return x * y == 8;};

  constexpr auto check8 = MakeCheck(xxxx);
cout << "vvvvv\n";

  auto rrrr = hana::chain(cross, check8);
  hana::for_each (rrrr, [](auto x){hana::unpack(x, pr);});

cout << "Sdfsdfsdf\n";

  auto tttt = hana::transform(cross, check8);
  hana::for_each (tttt, [](auto x){hana::unpack(hana::at_c<0>(x), pr);});


constexpr auto is_integral = hana::compose(hana::trait<std::is_integral>, hana::decltype_);
static_assert(hana::filter(hana::make_tuple(1, 2.0, 3, 4.0), is_integral) == hana::make_tuple(1, 3), "");

auto constexpr test = [xxxx](const auto x){return hana::bool_c< hana::unpack(x, xxxx) ? 0 : 1>;};
//auto constexpr test = [xxxx](auto x){return hana::unpack(x, xxxx) ? hana::false_c : hana::true_c;};
auto rr = test(hana::make_tuple(2, 4));


cout << "mmmmmm\n";
//  auto yyy = hana::filter(cross, [xxxx](auto x){hana::unpack(x, xxxx) ? hana::true_c : hana::false_c;});
  //auto yyy = hana::filter(cross, [xxxx](auto x){return true ? hana::true_c : hana::false_c;});
  auto yyy = hana::filter(cross, test);
  //auto yyy = hana::filter(cross, test);
  //auto yyy = hana::filter(cross, hana::true_c);
  hana::for_each (yyy, [](auto x){hana::unpack(x, pr);});

}
