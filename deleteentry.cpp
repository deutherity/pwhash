#include "const_pwhash.hpp"
#include "crash.hpp"
#include "readconf.hpp"
#include "util.hpp"
#include "writeconf.hpp"

void entrydel(const argvec &argv) {
    int id;
    try {
        id = std::stoi(std::string(argv.at(1)));
    } catch (const std::exception &e) {
        crash("Usage:\npwhash d[elete] {id}");
    }
    auto passwds = readconf();
    auto found = std::find_if(passwds.begin(), passwds.end(),
                              [&](const auto &i) { return i.m_id == id; });
    if (found == passwds.end()) {
        crash("Not found");
    }
    std::cout << "Found this entry:\n"
              << (*found).pretty()
              << "\nDo you really want to delete this entry?";
    if (confirm()) {
        (*found).devalidate();
        writeconf(passwds, mode::REWRITE);
        std::cout << "Done" << std::endl;
    }
}