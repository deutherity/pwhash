#include <string_view>
#include "const_pwhash.hpp"
#include "readconf.hpp"
#include "writeconf.hpp"
#include <iostream>
#include "util.hpp"
#include <unistd.h>
extern "C" 
{
    #include "clipcopy.h"
}

void gennew(const argvec& argv)
{
    int length;
    std::cout << "Length: ";
    std::cin >> length; 
    std::cout << "Service: ";
    char service[100];
    std::cin.ignore(10000, '\n');
    std::cin.getline(service, 100);
    auto passwds = readconf();
    auto comp = [](const auto& a, const auto& b) { return a.m_id < b.m_id; };
    int id = 1 + (*std::max_element(passwds.cbegin(), passwds.cend(), comp)).m_id;
    char add_alphabet[100];
    std::cout << "Additional letters: ";
    //std::cin.ignore(10000, '\n');
    std::cin.getline(add_alphabet, 256);
    std::cout << "Description: ";
    std::cout.flush();
    char description[256];
    //std::cin.ignore(10000, '\n');
    std::cin.getline(description, 256, '\n');
    Password<char> newpasswd;
    newpasswd.m_id = id;
    newpasswd.m_service = service;
    newpasswd.m_length = length;
    newpasswd.m_description = description;
    newpasswd.m_add_alphabet = add_alphabet;
    std::cout << "Should i generate salt?";
    if (confirm())
    newpasswd.makeSalt();
    std::cout << "Made this entry in list:" << std::endl << newpasswd.pretty() << std::endl;
    std::cout << "Want to check?";
    if (confirm())
    {
        char * passwd = getpass("Enter password: "); 
      tryAgane:
        clipcopy(newpasswd.cook(passwd).c_str());
        std::cout << "pwhash pasted into clipboard\n";
        std::cout << "Remake that password?";
        if (confirm())
        {
            newpasswd.m_id += 1;
            goto tryAgane;
        }
    }
    passwds.clear();
    passwds.push_back(newpasswd);
    writeconf(passwds);
    std::cout << "Saved id: " << newpasswd.m_id << std::endl;
}