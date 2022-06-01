#include <deque>
#include <map>
#include <iostream>
#include <string>

int main()
{
  std::map<char, std::deque<char>> rep = 
    {{'a', {'A', 'B', 'a', 'C', 'D'}},
     {'b', {'E'}},
     {'r', {'r', 'F'}}};

  std::string magic = "abracadabra";
  for(auto it = magic.begin(); it != magic.end(); ++it)
  {
    if(auto f = rep.find(*it); f != rep.end() && !f->second.empty())
    {
      *it = f->second.front();
      f->second.pop_front();
    }
  }

  std::cout << magic << "\n";
}

/*
  the first 'a' with 'A'
the second 'a' with 'B'
the fourth 'a' with 'C'
the fifth 'a' with 'D'
the first 'b' with 'E'
the second 'r' with 'F'
*/

/// AErBcadCbFD
/// AErBcadCbFD
