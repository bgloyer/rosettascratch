#include <iostream>

// apply the function zero times (return an identity function)
auto Zero() {
    return [](auto) {
        return [=](auto x) {return x;};
    };
}

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
        auto a_minus_b = b([](auto c){ return Predecessor(c);})(a);

        // Each lambda has its own type which gives '3-1' a different
        // type than '4-2'.  Normalize the number based on successors to 0.  
        return a_minus_b([=](auto f) {return Successor(f);})(Zero());
    };
}

namespace
{
    // helper functions for division.  These funtions are only
    // visible in this source file

    // end the recusrion
    auto Divr(decltype(Zero()), auto) {
        return Zero();
    }

    // count how many times b can be subtracted from a
    auto Divr(auto a, auto b) {
        return Successor(Divr(Subtract(a, b), b));
    }
}

// apply the function a / b times
auto Divide(auto a, auto b) {
    return Divr(Subtract(Successor(a), b), b);
}

// create a Church numeral from an integer at compile time
template <int N> constexpr auto ToChurch() {
    if constexpr(N<=0) return Zero();
    else return Successor(ToChurch<N-1>());
}

// use an increment function to convert the Church number to an integer
int ToInt(auto church) {
    return church([](int n){return n + 1;})(0);
}

int main() {
    // show some examples
    auto zero = Zero();
    auto three = Successor(Successor(Successor(zero)));
    auto four = Successor(three);
    auto six = ToChurch<6>();
    auto nine = ToChurch<9>();
    auto ten = Successor(nine);

    std::cout << "\n 3 + 4 = " << ToInt(Add(three, four));
    std::cout << "\n 4 + 3 = " << ToInt(Add(four, three));
    std::cout << "\n 3 * 4 = " << ToInt(Multiply(three, four));
    std::cout << "\n 4 * 3 = " << ToInt(Multiply(four, three));
    std::cout << "\n 3^4 = " << ToInt(Exp(three, four));
    std::cout << "\n 4^3 = " << ToInt(Exp(four, three));
    std::cout << "\n 0^0 = " << ToInt(Exp(zero, zero));
    std::cout << "\n 9 - 6 = " << ToInt(Subtract(nine, six));
    std::cout << "\n 9 - 9 = " << ToInt(Subtract(nine, nine));
    std::cout << "\n 6 / 3 = " << ToInt(Divide(six, three));
    std::cout << "\n 3 / 6 = " << ToInt(Divide(three, six));
    auto looloolooo = Add(Exp(ten, nine), Add(Exp(ten, six), Exp(ten, three)));
    auto looloolool = Successor(looloolooo);
    std::cout << "\n 10^9 + 10^6 + 10^3 + 1 = " << ToInt(looloolool) << "\n";
}
