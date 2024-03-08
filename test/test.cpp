#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    std::string s("abcd");
    do
    {
        std::cout << s << "\n";
    }
    while ( std::next_permutation(s.begin(), s.end()) );
}