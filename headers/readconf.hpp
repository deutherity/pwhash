#include <memory>
#include "Password.hpp"
#include <vector>

typedef std::vector<std::unique_ptr<Password>> passvec;

passvec && read_conf_file();