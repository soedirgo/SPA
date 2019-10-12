#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "PKBHash.h"

namespace Dispatcher {
    void dispatch(std::string rel,
                  std::string lhs,
                  std::string rhs,
                  std::unordered_map<std::string, std::string>& decl,
                  bool& resultExists,
                  std::unordered_set<std::vector<std::string>>& results);
}
