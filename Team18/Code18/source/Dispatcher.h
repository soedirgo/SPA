#pragma once
#include "Clause.h"
#include "PKBHash.h"
#include "Result.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Evaluator {
    Result dispatch(Clause& clause,
                    std::unordered_map<std::string, std::string>& decl);
} // namespace Evaluator
