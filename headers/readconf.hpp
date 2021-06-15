#include "crash.hpp"
#include "findconfdir.hpp"
#include "templates.hpp"
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

template <typename CharT> using passvec = std::vector<Password<CharT>>;

template <typename CharT = char> passvec<CharT> readconf() {
    namespace fs = std::filesystem;
    fs::path p;
    using res_t = passvec<CharT>;
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
    res.reserve(7);
    while (!fi.eof()) {
        fi >> foo;
        if (foo.m_id != -1)
        {
            res.push_back(std::move(foo));
        }
        
    }
    fi.close();
    return res;
}
