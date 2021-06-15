#include "const_pwhash.hpp"
#include <string>
#include "crash.hpp"
#include "readconf.hpp"
#include <algorithm>
#include <unistd.h>
extern "C"
{
    #include "clipcopy.h"
}


void usepwd(const argvec& argv)
{
    int id;
    try
    {
        id = std::stoi(std::string(argv.at(1)));
    }
    catch(const std::exception& e)
    {
        crash("Usage:\npwhash use {id}");
    }
    auto passwds = readconf();
    auto found = std::find_if(passwds.cbegin(), passwds.cend(), [&](const auto& i){return i.m_id == id; });
    if (found == passwds.cend() || !((*found).valid()))
    {
        crash("Not found");
    }
    clipcopy((*found).cook(getpass("Enter password: ")).c_str());
    std::cout << "pwhash pasted into clipboard" << std::endl;
}