#include "const.hpp"
#include <string>
class Password
{
private:
    std::string service;
    std::string login;
    int number;
    std::string comment;
    int salt_len;
    uchar salt;
public:
    ~Password();
};

Password::Password()
{
}

Password::~Password()
{
}
