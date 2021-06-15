#include <vector>
#include <string_view>
#define CONFFILE "pwdb.conf"
#include <cstddef>
#define SALTLEN 256
typedef unsigned char uchar;
typedef std::vector<std::string_view> argvec;
bool less_or_eq(std::string_view tested, std::string_view wanted);