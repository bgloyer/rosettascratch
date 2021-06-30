#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct LoggingMonad
{
    double Value;
    string Log;
};

ostream& operator<<(ostream &os, const LoggingMonad &monad)
{
    os << monad.Log << "\nResult: " << monad.Value;
    return os;
}

// Use the >> operator as the bind function
auto operator>>(const LoggingMonad& monad, auto f)
{
    auto result = f(monad.Value);
    return LoggingMonad{result.Value, monad.Log + "\n" + result.Log};
}

auto Root = [](double x){ return sqrt(x); };
auto AddOne = [](double x){ return x + 1; };
auto Half = [](double x){ return x / 2.0; };

auto Writer = [](auto f, string message)
{
    return [=](double x){return LoggingMonad(f(x), message);};
};

int main()
{
    auto startingValue = LoggingMonad{5, "Starting with 5"};
    auto writerRoot = Writer(Root, "Taking square root");
    auto writerAddOne = Writer(AddOne, "Adding 1");
    auto writerHalf = Writer(Half, "Dividing by 2");    

    auto result = startingValue >> writerRoot >> writerAddOne >> writerHalf;
    
    cout << result;
}
