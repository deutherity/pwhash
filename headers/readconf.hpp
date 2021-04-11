#include "Password.hpp"
#include <memory>
#include <vector>

typedef std::vector<std::unique_ptr<Password>> passvec;

passvec &&read_conf_file();