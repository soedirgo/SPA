#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Query.h"

// class Evaluator {
// public:
//     static std::string evalQuery(Query q);
// private:
//     static std::vector<std::string, std::string> declarations;
//     static std::vector<Clause> clauses;
// };

namespace Evaluator {
    std::string evalQuery(Query q);
}
