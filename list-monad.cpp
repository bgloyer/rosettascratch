#include <algorithm>
#include <execution>
#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

#include <chrono>
class ScopeTimer
{
public:
        ScopeTimer(std::string name) : mName(std::move(name)), mStart(std::chrono::steady_clock::now()) { }
        ScopeTimer() : mName("Timer"), mStart(std::chrono::steady_clock::now()) { }
        ~ScopeTimer()
        {
                const auto end = std::chrono::steady_clock::now();
                std::cout << mName << ": " << std::chrono::duration <double, std::milli>(end - mStart).count() << " ms\n";
        }

private:
        const std::string mName;
        const std::chrono::time_point<std::chrono::steady_clock> mStart;
};


// std::vector can be a list monad.  Use the >> operator as the bind function
template <typename T>
auto operator>>(const vector<T>& monad, auto f)
{
    // Declare a vector of the same type that the function f returns
    vector<remove_reference_t<decltype(f(monad.front()).front())>> result;
    auto concat = [](auto v1, auto v2)
    {
        if(v1.size() < v2.size()) swap(v1, v2);
        v1.insert(v1.end(), begin(v2), end(v2));
        return v1;
    };
    
  //  transform(monad.begin(), monad.end(), result.begin(), f);
    //result = transform_reduce(execution::seq, monad.begin(), monad.end(), result, concat, f);

    vector<remove_reference_t<decltype(f(monad.front()))>> out(monad.size());
   // vector<int> out;
    transform(execution::par, monad.begin(), monad.end(), out.begin(), f);
 //   transform(monad.begin(), monad.end(), back_inserter(out), f);
    int count = 0;
    for(const auto& sub : out)
    {
        count += sub.size();
    }
//    result.reserve(count);
    for_each(out.begin(), out.end(), [&result](const auto& item)
    {
        result.insert(result.end(), item.begin(), item.end());
    });
//     for(const auto& sub : out)
//     {
//         result.insert(result.end(), begin(sub), end(sub));
//     }

    return result;
}

// The Pure function returns a vector containing one item, t
auto Pure(auto t)
{
    return vector{t};
}

// A function to double items in the list monad
auto Double(int i)
{
    return Pure(2 * i);
}

// A function to increment items
auto Increment(int i)
{
    return Pure(i + 1);
}

// A function to convert items to a string
auto NiceNumber(int i)
{
    return Pure(to_string(i) + " is a nice number\n");
}

const int MaxPerimeter = 5000;

// A function to map an item to a sequence ending at max value
// for example: 497 -> {497, 498, 499, 500}
auto UpperSequence = [](auto startingVal)
{
    vector<decltype(startingVal)> sequence;
    while(startingVal < MaxPerimeter/3) 
        sequence.push_back(startingVal++);
    return sequence;
};

auto RelativePrimePair = [](auto startingVal)
{
    vector<tuple<decltype(startingVal), decltype(startingVal)>> sequence;
    for(auto yVal = startingVal + 1; yVal < (MaxPerimeter - startingVal) / 2; ++yVal)
    {
        if(gcd(startingVal, yVal) == 1)
            sequence.emplace_back(startingVal, yVal);
    }
    return sequence;
};

auto Pythagorean = [](auto pair)
{
    auto [x, y] = pair;
    using valtype = decltype(x);
    valtype oddAdjustment = y % 2 + (x + y) % 2;
    vector<tuple<valtype, valtype, valtype>> pythagoreanTriples;
    for(auto z = y + oddAdjustment; x + y + z < MaxPerimeter; z += 2)
    {
        if(x*x + y*y == z*z)
            pythagoreanTriples.emplace_back(x, y, z);
    }
    return pythagoreanTriples;
};

// Print contents of a vector
void PrintVector(const auto& vec)
{
    cout << " ";
    for(auto value : vec)
    {
        cout << value << " ";
    }
    cout << "\n";
}

// Print the Pythagorean triples
void PrintTriples(const auto& vec)
{
    cout << vec.size() << " Pythagorean triples:\n";
    for(auto it = vec.begin(); it != vec.end();)
    {
        auto x = *it++;
        auto y = *it++;
        auto z = *it++;
        
        cout << x << ", " << y << ", " << z << "\n";
    }
    cout << "\n";
}

// Print the Pythagorean triples
void PrintTriples(const vector<tuple<int,int,int>>& vec)
{
    cout << vec.size() << " Pythagorean triples:\n";
    for(auto [x, y, z] : vec)
    {
        cout << x << ", " << y << ", " << z << "\n";
    }
    cout << "\n";
}


int main()
{
    // Apply Increment, Double, and NiceNumber to {2, 3, 4} using the monadic bind 
    auto listMonad = 
        vector<int> {2, 3, 4} >> 
        Increment >> 
        Double >>
        NiceNumber;
        
    PrintVector(listMonad);
    
//     // Find Pythagorean triples using the list monad.  The 'x' monad list goes
//     // from 1 to the max; the 'y' goes from the current 'x' to the max; and 'z'
//     // goes from the current 'y' to the max.  The last bind returns the triplet
//     // if it is Pythagorean, otherwise it returns an empty list monad.
//     auto pythagoreanTriples = UpperSequence(1) >> 
//         [](int x){return UpperSequence(x) >> 
//         [x](int y){ return UpperSequence(y) >>
//         [x, y](int z){return (x*x + y*y == z*z && gcd(x, y) == 1) ? vector{make_tuple(x, y, z)} : vector<tuple<int,int,int>>{};};};};

    ScopeTimer st;
    
    auto pythagoreanTriples = UpperSequence(1) >> 
        RelativePrimePair >>
        Pythagorean;

    
    PrintTriples(pythagoreanTriples);
}
