#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void PrintListMonad(const auto& vec)
{
    for(auto value : vec)
    {
        if constexpr (is_integral_v<decltype(value)>)
        {
            cout << value << " ";
        }
        else
        {
            cout << "[ ";
            for(auto v2 : value)
            {
                cout << v2 << " ";
            }
            cout << "]\n";
        }
        
    }
    cout << "\n";
}


template <typename T>
auto operator>>(const vector<T>& m, auto f)
{
    vector<remove_reference_t<decltype(f(m.front()).front())>> result;
    for(auto& item : m)
    {
        const auto r = f(item);
        result.insert(result.end(), begin(r), end(r));
    }
    
    return result;
}

auto Pure(auto t)
{
    return vector{t};
}

auto Double(int i)
{
    return Pure(2 * i);
}

auto Increment(int i)
{
    return Pure(i + 1);
}

auto UpperSequence = [](auto startingVal)
{
    vector<decltype(startingVal)> sequence;
    while(startingVal <= 500) 
        sequence.push_back(startingVal++);
    return sequence;
};

//auto CheckPythagorean = [

int main()
{
  
    auto zzz = 
        vector<int> {2, 3, 4} >> 
        Increment >> 
        Double;
    
    
    PrintListMonad(zzz);
    
    auto sss = UpperSequence(1) >> 
        [](int x){return UpperSequence(x) >>
        [x](int y){return UpperSequence(y) >>
        [x, y](int z){return (x*x + y*y == z*z) ? vector{x, y, z} : vector<int>{};};};};
    
    
    PrintListMonad(sss);
    
                
            
}
