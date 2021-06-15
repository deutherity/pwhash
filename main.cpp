#include <string>
#include <string_view>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <algorithm>
#include "const_pwhash.hpp"
#include "util.hpp"

namespace fs = std::filesystem;
std::string get_conf_path();

bool printhelp();
void checklist(const argvec& argv);
int getpwd(argvec & args, const char * passwd, std::string confpath);

void gennew(const argvec& argv);
void usepwd(const argvec& argv);




int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    argvec args;
    if (argc == 1)
    {
        printhelp();
        return 0;
    }
    for (auto i = 1; i < argc; i++)
    {
        if (less_or_eq(argv[i], "help") || std::memcmp(argv[i], "-h", 3) == 0 || std::memcmp(argv[i], "--help", 7) == 0)
        {
            printhelp();
            return 0;
        }
        args.push_back(std::string_view(argv[i]));
    }
     if (std::any_of(args.cbegin(), args.cend(), [&](auto i){ return less_or_eq(i, "list"); }))
    {
        checklist(args);
        return 0;
    }

   if (std::any_of(args.cbegin(), args.cend(), [&](auto i){ return less_or_eq(i, "new"); }))
    {
        gennew(args);
        return 0;
    }

   if (less_or_eq(argv[1], "use"))
    {
        usepwd(args);
        return 0;
    }

    printhelp();



/*
    else if (less_or_eq(args[1], "get"))
    getpwd(args, passwd, confpath);
*/
    return 0;
}
