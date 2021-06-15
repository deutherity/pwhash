#include <string_view>
#include "const_pwhash.hpp"
#include "readconf.hpp"

#define STICK "============================\n"

void checklist(const argvec& argv)
{
    std::cout << STICK;
    for (const auto& i: readconf())
    {
        if (i.valid())
            std::cout << i.pretty() << '\n' << STICK;
    } 
}