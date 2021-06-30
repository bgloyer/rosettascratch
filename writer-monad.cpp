#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class LoggingMonad
{
    double m_value;
    string m_log;
    
public:
    LoggingMonad(double value, string log) :
    m_value(value), m_log(move(log))
    {}
    
    double Value() const
    {
        return m_value;
    }
    
    string Log() const
    {
        return m_log;
    }
};

    ostream& operator<<(ostream &os, const LoggingMonad &monad)
    {
        os << monad.Log() << "\nResult: " << monad.Value();
        return os;
    }


// Use the >> operator as the bind function
auto operator>>(const LoggingMonad& monad, auto f)
{
    auto result = f(monad.Value());
    return LoggingMonad(result.Value(), monad.Log() + "\n" + result.Log());
}

double Root(double d)
{
    return sqrt(d);
}

double AddOne(double d)
{
    return d + 1;
}

double Half(double d)
{
    return d / 2.0;
}

auto Writer(auto f, string message)
{
    return [=](double d){return LoggingMonad(f(d), message);};
}


int main()
{
    auto startingValue = LoggingMonad(5, "Starting with 5");
    auto writerRoot = Writer(Root, "Taking square root");
    auto writerAddOne = Writer(AddOne, "Adding 1");
    auto writerHalf = Writer(Half, "Dividing by 2");    

    auto result = startingValue >> writerRoot >> writerAddOne >> writerHalf;
    
    cout << result;
}
