#pragma once
#include "Result.h"
#include <string>
#include <vector>

namespace Evaluator {
    std::vector<std::vector<Result>> group(std::vector<Result>& results,
                                           std::vector<std::string>& selSyns);
    void sort(std::vector<Result>& results);
} // namespace Evaluator
