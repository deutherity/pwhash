#include "readconf.hpp"
#include "crash.hpp"
#include "findconfdir.hpp"
#include "templates.hpp"
#include <fstream>

template <typename CharT = char> passvec<CharT> readconf() {
    using res_t = passvec<CharT>;
    fs::path p;
    try {
        p = findconfdir();
    } catch (const int &e) {
        crash("Config directory is corrupted");
    }

    res_t res;
    p /= "pwdb.txt";
    if (!fs::exists(p)) {
        std::fstream fi(p.string(), std::fstream::out);
        fi << std::endl;
        fi.close();
    } else if (!fs::is_regular_file(p))
        crash("Data file is corrupted");

    std::fstream fi(p.string(), std::fstream::in);
    if (!fi.is_open())
        crash("Failed to open data");

    Password<CharT> foo;
    while (!fi.eof()) {
        fi >> foo;
        res.push_back(std::move(foo));
    }
    return res;
}
