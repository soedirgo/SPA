#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "PKBHash.h"
#include "Clause.h"

namespace Evaluator {
    void dispatch(Clause& clause,
                  std::unordered_map<std::string, std::string>& decl,
                  bool& resultExists,
                  std::unordered_map<std::string, int>& synonyms,
                  std::unordered_set<std::vector<std::string>>& results);
} // namespace Evaluator
