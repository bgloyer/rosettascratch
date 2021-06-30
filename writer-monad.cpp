#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// Use a struct as the monad
struct LoggingMonad
{
    double Value;
    string Log;
};

// Use the >> operator as the bind function
auto operator>>(const LoggingMonad& monad, auto f)
{
    auto result = f(monad.Value);
    return LoggingMonad{result.Value, monad.Log + "\n" + result.Log};
}

// Define the three simple functions
auto Root = [](double x){ return sqrt(x); };
auto AddOne = [](double x){ return x + 1; };
auto Half = [](double x){ return x / 2.0; };

// Define a function to create writer monads from the simple functions
auto Writer = [](auto f, string message)
{
    return [=](double x){return LoggingMonad(f(x), message);};
};

// Derive writer versions of the simple functions
auto writerRoot = Writer(Root, "Taking square root");
auto writerAddOne = Writer(AddOne, "Adding 1");
auto writerHalf = Writer(Half, "Dividing by 2");


int main()
{
    auto result = LoggingMonad{5, "Starting with 5"} >> writerRoot >> writerAddOne >> writerHalf;
    cout << result.Log << "\nResult: " << result.Value;
}
