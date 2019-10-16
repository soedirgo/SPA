#pragma once
#include "Clause.h"
#include "Result.h"
#include <string>
#include <unordered_map>

namespace Evaluator {
    Result dispatch(Clause& clause,
                    std::unordered_map<std::string, std::string>& decl);
} // namespace Evaluator
