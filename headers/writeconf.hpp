#include "crash.hpp"
#include "findconfdir.hpp"
#include "templates.hpp"
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>
namespace fs = std::filesystem;
enum class mode { ADD, REWRITE };

template <typename CharT> using passvec = std::vector<Password<CharT>>;

template <typename CharT = char>
void writeconf(passvec<CharT> input, mode t_mode = mode::ADD) {
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

    std::fstream fo(p.string(), (t_mode == mode::ADD) ? std::fstream::app
                                                      : std::fstream::out);
    if (!fo.is_open())
        crash("Failed to open data");

    for (auto i : input) {
        fo << i << '\n';
    }
    fo.close();
}
