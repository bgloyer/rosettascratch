#include <iostream>

// apply the function zero times (return an identity function)
auto Zero() {
    return [](auto) {
        return [=](auto x) {return x;};
    };
}

// apply the function f one more time
auto Successor(auto church) {
    return [=](auto f) {
        return [=](auto x) {
            return church(f)(f(x));
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
    auto looloolooo = Add(Exp(ten, nine), Add(Exp(ten, six), Exp(ten, three)));
    std::cout << "\n 10^9 + 10^6 + 10^3 = " << ToInt(looloolooo) << "\n";
}
