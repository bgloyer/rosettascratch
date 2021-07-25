#include <algorithm>
#include <execution>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <tuple>
#include <vector>

#include "ScopeTimer.h"

using namespace std;

auto BruteForcePythagorean(unsigned int perimeter)
{
    unsigned int primitiveCount = 0;
    unsigned int totalCount = 0;
    unsigned int yless = 0;
    unsigned int zless = 0;
    unsigned int nongcd = 0;
    for(unsigned long long x = 1; x <= perimeter / 2; ++x)
    {
        const auto xx = x * x;
        for(unsigned long long y = x + 1; y < (perimeter - x) / 2; ++y)
        {
            if(gcd(x, y) == 1)
            {
                const auto yy = y * y;
                unsigned long long oddAdjustment = y % 2 + (x + y) % 2;
                for(unsigned long long z = y + oddAdjustment; x + y + z < perimeter; z+=2)
                {
                    if(xx + yy == z*z)
                    {
                        primitiveCount++;
                        totalCount += perimeter / (x + y + z);
  //                      if(y < x) yless++;
   //                     if(z < y) zless++;
   //                     if(gcd(y, z) != 1)
     //                   {
       //                     nongcd++;
         //                   cout << "\nx " << x << ", y " << y << ",z " << z << ", gcd_y_z: " << gcd(y, z) << 
           //                 ", x*x+y*y " << x*x + y*y << ", z*z " << z*z <<  endl;
             //           }
                    }
                }
            }
        }
    }
    cout << "\nyless:" << yless;
    cout << "\nzless:" << zless;
    cout << "\nnongcd:" << nongcd;
    return make_tuple(totalCount, primitiveCount);
}

unsigned int MaxPerimeter = 100000;
unsigned int prim = 0;
unsigned int total = 0;


void NewTri(unsigned int s0, unsigned int s1, unsigned int s2) {
    auto p = s0 + s1 + s2;
    if (p <= MaxPerimeter) {
      prim++;
      total += int(MaxPerimeter / p);
      NewTri(+1*s0-2*s1+2*s2,+2*s0-1*s1+2*s2,+2*s0-2*s1+3*s2);
      NewTri(+1*s0+2*s1+2*s2,+2*s0+1*s1+2*s2,+2*s0+2*s1+3*s2);
      NewTri(-1*s0+2*s1+2*s2,-2*s0+1*s1+2*s2,-2*s0+2*s1+3*s2);
    }
}

void NewTri2(unsigned int s0, unsigned int s1, unsigned int s2) {
    auto p = s0 + s1 + s2;
    if (p <= MaxPerimeter) {
      prim++;
      total += int(MaxPerimeter / p);
    }
    if (p <= MaxPerimeter * 2 ) {
      NewTri2(+1*s0-2*s1+2*s2,+2*s0-1*s1+2*s2,+2*s0-2*s1+3*s2);
      NewTri2(+1*s0+2*s1+2*s2,+2*s0+1*s1+2*s2,+2*s0+2*s1+3*s2);
      NewTri2(-1*s0+2*s1+2*s2,-2*s0+1*s1+2*s2,-2*s0+2*s1+3*s2);
    }
}
void CountTripletsTri()
{
    prim = 0;
    total = 0;
    MaxPerimeter = 1000000000;
    
    cout << "\n total: " << total;
    cout << " prim: " << prim;

    NewTri2(3,4,5);
    
    cout << "\n total: " << total;
    cout << " prim: " << prim;

    
    prim = 0;
    total = 0;
    //MaxPerimeter = 1000000;

    cout << "\n total: " << total;
    cout << " prim: " << prim;
    
    NewTri(3,4,5);
    
    cout << "\n total: " << total;
    cout << " prim: " << prim;
        
}

auto CountTriplets(unsigned long long maxPerimeter)
{
    unsigned long long totalCount = 0;
    unsigned long long primitveCount = 0;
    auto max_M = (unsigned long long)sqrt(maxPerimeter/2) + 1;
    for(unsigned long long m = 2; m < max_M; ++m)
    {
        for(unsigned long long n = 1 + m % 2; n < m; n+=2)
        {
            if(gcd(m,n) != 1)
            {
                continue;
            }
            
            auto a = m * m - n * n;
            auto b = 2 * m * n;
            auto c = m * m + n * n;
            auto perimeter = a + b + c;
            if(perimeter <= maxPerimeter)
            {
                primitveCount++;
                totalCount+= maxPerimeter / perimeter;
            }
        }
    }
    
    return tuple(totalCount, primitveCount);
}


void Print(std::ranges::forward_range auto r)
{
    cout << "\n";
    for(const auto [total, primitive] : r)
    {
        cout << "\nTotal: " << total << ", Primitive: " << primitive ;
    }
}

int main_py()
{
    ScopeTimer st;
    vector<unsigned long long> inputs{100, 1000, 10'000, 100'000,
        1000'000, 10'000'000, 100'000'000, 1000'000'000,
        10'000'000'000};  // This last one takes almost a minute
    for(auto maxPerimeter : inputs)
    {
        auto [total, primitive] = CountTriplets(maxPerimeter);
        cout << "\nMax Perimeter: " << maxPerimeter << ", Total: " << total << ", Primitive: " << primitive ;
    }
}
