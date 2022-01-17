#include <iostream>
#include <boost/hana.hpp>
#include <boost/hana/experimental/printable.hpp>
#include <string_view>

using namespace std;
namespace hana = boost::hana;

void pr(int a, int b)
{
  cout << "ab: " << a << ", " << b << "\n";
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
//    if (isValid) return hana::tuple<decltype(x)>{x};
    if (isValid) return x;
//    else return hana::tuple<hana::empty<decltype(x)>>{x};
//    else return hana::empty<decltype(hana::tuple<decltype(x)>)();
//    else return hana::empty<hana::tuple<hana::tuple<int, int>>>();
    else return hana::empty<hana::tuple<int, int>>();
//    else return hana::tuple<hana::empty<hana::tuple<int, int>>>();
  };
}

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


template<typename ...Args>
void printer(Args&&... args)
{
    (std::cout << ... << args) << '\n';
}

template<typename Args>
constexpr bool FirstMatchesLast(Args args)
{
  return true;
}

constexpr bool Matches(const auto& t)
{
  auto l = hana::length(t);
  bool match = true;
  for(int i = 1; i < l; ++i)
  {
    match &= t[i-1].back() == t[i].front();
  }
  return match;
}

template<typename T>
constexpr bool matches2 (T t)
{
  constexpr auto l = hana::length(t);
  constexpr bool match = l < 0 ? true :
    t[0].back() == t[1].front() && matches(hana::drop_front(t));
//    for(int i = 1; i < l; ++i)
//   {
///    match &= ;
  // }
  return match;
}


// template<typename ...Args>
// constexpr bool FirstMatchesLast(string_view sv, Args&&... args)
// {
//   return sv.back() == args.front && FirstMatchesLast(args, ...);
// //  if(sv.back() == args.front()) return FirstMatchesLast(args, ...);
// //  else return false && ;
// }


int main()
{
  hana::tuple x{1, 2, 3};
  hana::tuple y{7, 6, 4, 5};

  hana::tuple tuples{x, y};

  auto cross = hana::cartesian_product(tuples);

  hana::for_each (cross, [](auto x){hana::unpack(x, pr);});

  constexpr auto xxxx = [](int x, int y){return x * y == 8;};

  constexpr auto check8 = MakeCheck(xxxx);

  constexpr auto foldOp = Folder(xxxx);
  auto result = hana::fold_right(cross, foldOp); 
  cout << "vvvvv\n";
  hana::unpack(result, pr);
//  hana::for_each (result, [](auto x){hana::unpack(x, pr);});
  cout << "words\n";

  auto words1 = hana::make_tuple("the"sv, "that"sv, "a"sv);
  auto words2 = hana::make_tuple("frog"sv, "elephant"sv, "thing"sv);
  auto words3 = hana::make_tuple("walked"sv, "treaded"sv, "grows"sv);
  auto words4 = hana::make_tuple("slowly"sv, "quickly"sv);
  // auto words1 = hana::make_tuple("that"sv, "a"sv);
  // auto words2 = hana::make_tuple("thing"sv);
  // auto words3 = hana::make_tuple("grows"sv);
  // auto words4 = hana::make_tuple("slowly"sv, "quickly"sv);


  auto wordsCross = hana::cartesian_product(hana::tuple{words1, words2, words3, words4});

  cout << hana::experimental::print(wordsCross) << "\n";

  constexpr auto matches = [](const auto t)
  {
    auto first = hana::drop_back(t);
    auto last = hana::drop_front(t);
    auto adjacent = hana::zip(first, last);
    cout << "\nt: " << hana::experimental::print(t);
    cout << "\nadjacent: " << hana::experimental::print(adjacent) << "\n";
    auto bools = hana::transform(adjacent, [](auto t)
    {
      return t[hana::size_c<0>].back() == t[hana::size_c<1>].front();
    });
    cout << "\nbools: " << hana::experimental::print(bools) << "\n";
    auto match = hana::fold_right(bools, [](bool b1, bool b2)
    {
      return b1 && b2;
    });
    cout << "dddd" << hana::experimental::print(match) << "\n";
//    constexpr auto l = hana::length(t);
//    constexpr bool match = l < 0 ? true :
 //     t[0].back() == t[1].front() && matches(hana::drop_front(t));
//    for(int i = 1; i < l; ++i)
 //   {
  ///    match &= ;
   // }
  //return true;
    return match;
  };

  constexpr auto foldWordsOp = Folder2(matches);
  auto wordResult = hana::fold_right(wordsCross, foldWordsOp);
  cout << "word Results: " << hana::experimental::print(wordResult) << "\n";
  //cout << "end";

  hana::tuple cccc{hana::tuple{1, 2}, hana::tuple{3,4}};
  hana::for_each (cccc, [](auto x){hana::unpack(x, pr);});
  auto cccc2 = hana::append(cccc, hana::tuple{5,6});
  hana::for_each (cccc2, [](auto x){hana::unpack(x, pr);});
  auto cccc4 = hana::fold_right(cccc, foldOp);
  hana::unpack(cccc4, pr);
  //auto cccc3 = hana::append(cccc2, hana::empty<hana::tuple<int, int>>());
//  auto cccc3 = hana::append(cccc2, hana::empty<hana::tuple_tag>());
//  hana::for_each (cccc3, [](auto x){hana::unpack(x, pr);});


  //auto rrrr = hana::chain(cross, check8);
  //hana::for_each (rrrr, [](auto x){hana::unpack(x, pr);});

cout << "Sdfsdfsdf\n";

  auto tttt = hana::transform(cross, check8);
  hana::for_each (tttt, [](auto x){hana::unpack(x, pr);});
//  auto yyyy = hana::remove(tttt, hana::empty<hana::tuple<int, int>>());
//  hana::for_each (tttt, [](auto x){hana::unpack(hana::at_c<0>(x), pr);});


//constexpr auto is_integral = hana::compose(hana::trait<std::is_integral>, hana::decltype_);
//static_assert(hana::filter(hana::make_tuple(1, 2.0, 3, 4.0), is_integral) == hana::make_tuple(1, 3), "");

//auto constexpr test = [xxxx](const auto x){return hana::bool_c< hana::unpack(x, xxxx) ? 0 : 1>;};
//auto constexpr test = [xxxx](auto x){return hana::unpack(x, xxxx) ? hana::false_c : hana::true_c;};
//auto rr = test(hana::make_tuple(2, 4));


cout << "mmmmmm\n";
//  auto yyy = hana::filter(cross, [xxxx](auto x){hana::unpack(x, xxxx) ? hana::true_c : hana::false_c;});
  //auto yyy = hana::filter(cross, [xxxx](auto x){return true ? hana::true_c : hana::false_c;});
  //auto yyy = hana::filter(cross, test);
  //auto yyy = hana::filter(cross, test);
  //auto yyy = hana::filter(cross, hana::true_c);
 // hana::for_each (yyy, [](auto x){hana::unpack(x, pr);});

}
