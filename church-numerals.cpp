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

// apply the Successor function a times to b
auto SlowAdd(auto a, auto b) {
    {
        return a([](auto c){ return Successor(c);})(b);
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
// f => x => n(g => h => h(g(f)) )(_ => x)(a => a);
auto Predecessor(auto n) {
    return [=](auto f) {
        return [=](auto x) {
            return n(
                [=](auto g) {
                    return [=](auto h){
                        return h(g(f));
                    };
                }
             )([=](auto) {return x;})([](auto a){return a;});
        };
    };
}

// apply the Successor function a times to b
auto Subtract(auto b, auto a) {
    {
        return a([](auto c){ return Predecessor(c);})(b);
    };
}


//    public static Church Predecessor(this Church n) =>

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
    
    std::cout << "\n Pred(3) = " << ToInt(Predecessor(three));
    std::cout << "\n 3 + 4 = " << ToInt(Add(three, four));
    std::cout << "\n 4 + 3 = " << ToInt(Add(four, three));
    std::cout << "\n 6 + 9 = " << ToInt(SlowAdd(six, nine));
    std::cout << "\n 9 - 6 = " << ToInt(Subtract(nine, six));
    std::cout << "\n 3 * 4 = " << ToInt(Multiply(three, four));
    std::cout << "\n 4 * 3 = " << ToInt(Multiply(four, three));
    std::cout << "\n 3^4 = " << ToInt(Exp(three, four));
    std::cout << "\n 4^3 = " << ToInt(Exp(four, three));
    std::cout << "\n 0^0 = " << ToInt(Exp(zero, zero));
    auto looloolooo = Add(Exp(ten, nine), Add(Exp(ten, six), Exp(ten, three)));
    auto looloolool = Successor(looloolooo);
    std::cout << "\n 10^(3-1) -1  " << ToInt(Predecessor(Exp(ten, Predecessor(three))));

    std::cout << "\n 10^9 + 10^6 + 10^3 + 1 = " << ToInt(looloolool) << "\n";
}
