#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace Validator {
    bool isPatternValid(std::vector<std::string>& fields,
                        std::unordered_map<std::string, std::string>& declarationMap);
}
