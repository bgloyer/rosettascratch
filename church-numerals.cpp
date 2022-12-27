#include <iostream>

// apply the function zero times (return an identity function)
auto Zero = [](auto){return [](auto x) {return x;};};

// define Church True and False
auto True = [](auto a){return [=](auto){return a;};};
auto False = [](auto){return [](auto b){return b;};};

// apply the function f one more time
auto Successor(auto a) {
    return [=](auto f) {
        return [=](auto x) {
            return a(f)(f(x));
        };
    };
}

// apply the function a times after b times
auto Add(auto a, auto b) {
    return [=](auto f) {
        return [=](auto x) {
            return a(f)(b(f)(x));
        };
    };
}

// apply the function a times b times
auto Multiply(auto a, auto b) {
    return [=](auto f) {
        return a(b(f));
    };
}

// apply the function a^b times
auto Exp(auto a, auto b) {
    return b(a);
}

// Check if a number is zero
auto IsZero(auto a){
    return a([](auto){return False;})(True);
}

// apply the function f one less time
auto Predecessor(auto a) {
    return [=](auto f) {
        return [=](auto x) {
            return a(
                [=](auto g) {
                    return [=](auto h){
                        return h(g(f));
                    };
                }
             )([=](auto) {return x;})([](auto y){return y;});
        };
    };
}

// apply the Predecessor function b times to a
auto Subtract(auto a, auto b) {
    {
        return b([](auto c){ return Predecessor(c);})(a);
    };
}

namespace
{
    // helper functions for division.  These funtions are only
    // visible in this source file

    // end the recusrion
    auto Divr(decltype(Zero), auto) {
        return Zero;
    }

    // count how many times b can be subtracted from a
    auto Divr(auto a, auto b) {
        auto a_minus_b = Subtract(a, b);
        auto isZero = IsZero(a_minus_b);

        return isZero
                    (Zero)
                    (Successor(Divr(isZero(Zero)(a_minus_b), b)));
    }


}

// apply the function a / b times
auto Divide(auto a, auto b) {
    return Divr(Successor(a), b);
}

// create a Church numeral from an integer at compile time
template <int N> constexpr auto ToChurch() {
    if constexpr(N<=0) return Zero;
    else return Successor(ToChurch<N-1>());
}

// use an increment function to convert the Church number to an integer
int ToInt(auto church) {
    return church([](int n){return n + 1;})(0);
}

auto One = ToChurch<1>();

void CSix(decltype(Zero))
{
    std::cout << "\n got Zero";
}

    // auto True = [](auto a){return [=](auto){return a;};};
    // auto False = [](auto){return [](auto b){return b;};};
    // auto IsZero = [](auto a){return a([](auto){return False;})(True);};


auto NormalizeZero(auto n)
{
//    auto z = IsZero(n);
 //   return z(Zero())(n);
    return IsZero(n)(Zero)(n);
//      return a([](auto){return Zero();})(a);
}

//auto IfZero(auto)

int main() {


    // show some examples
    auto zero = Zero;
    auto three = Successor(Successor(Successor(zero)));
    auto four = Successor(three);
    auto six = ToChurch<6>();
    auto nine = ToChurch<9>();
    auto ten = Successor(nine);

    std::cout << "\n t? 3  4 = " << ToInt(True(three)(four));
    std::cout << "\n f? 3  4 = " << ToInt(False(three)(four));
    std::cout << "\n 3 + 4 = " << ToInt(NormalizeZero(Add(three, four)));
    std::cout << "\n 0 = " << ToInt(NormalizeZero(Zero));
    std::cout << "\n 1 - 1 = " << ToInt(NormalizeZero(Subtract(One, One)));
    CSix(Zero);
    CSix(NormalizeZero(Subtract(One, One)));
//    CSix(Successor(Predecessor(Six)));

    //auto threeXtwo = Multiply(ToChurch<3>(), ToChurch<2>());
    //CSix(threeXtwo);


    std::cout << "\n 3 + 4 = " << ToInt(Add(three, four));
    std::cout << "\n 4 + 3 = " << ToInt(Add(four, three));
    std::cout << "\n 3 * 4 = " << ToInt(Multiply(three, four));
    std::cout << "\n 4 * 3 = " << ToInt(Multiply(four, three));
    std::cout << "\n 3^4 = " << ToInt(Exp(three, four));
    std::cout << "\n 4^3 = " << ToInt(Exp(four, three));
    std::cout << "\n 0^0 = " << ToInt(Exp(zero, zero));
    std::cout << "\n 9 - 6 = " << ToInt(Subtract(nine, six));
    std::cout << "\n 9 - 9 = " << ToInt(Subtract(nine, nine));
    std::cout << "\n X - Y = " << ToInt(Subtract(ToChurch<40>(), ToChurch<0>()));
//    std::cout << "\n Pred = " << ToInt(Predecessor(ToChurch<40>()));
    std::cout << "\n 6 / 3 = " << ToInt(Divide(six, three));
    std::cout << "\n 9 / 2 = " << ToInt(Divide(ToChurch<22>(), ToChurch<2>()));
    std::cout << "\n 3 / 3 = " << ToInt(Divide(ToChurch<3>(), ToChurch<3>()));
    std::cout << "\n 2 / 3 = " << ToInt(Divide(Successor(One), three));
    std::cout << "\n 0 / 3 = " << ToInt(Divide(Zero, three));
    //auto looloolooo = Add(Exp(ten, nine), Add(Exp(ten, six), Exp(ten, three)));
    //auto looloolool = Successor(looloolooo);
    
    //std::cout << "\n 10^9 + 10^6 + 10^3 + 1 = " << ToInt(looloolool) << "\n";
    std::cout << "\n golden ratio = " << Exp(ten, three)([](double x){return 1.0 + 1.0 / x;})(1.0) << "\n";

}
