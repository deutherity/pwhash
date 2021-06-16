#include "const_pwhash.hpp"
#include "readconf.hpp"
#include <string_view>

#define STICK "============================\n"

void checklist(const argvec &argv) {
    std::cout << STICK;
    for (const auto &i : readconf()) {
        if (i.valid())
            std::cout << i.pretty() << '\n' << STICK;
    }
}