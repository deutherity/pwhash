#include <iostream>
#include "const_pwhash.hpp"
#include "genhash.hpp"
#include "genpw.hpp"
#include <cstdlib>
#include <string>

int main(int argc, char const *argv[])
{
    std::string s;
    std::cin >>s;
    std::string ret = genpw(s, 64);
    std::cout << ret << std::endl;
    return 0;
}
