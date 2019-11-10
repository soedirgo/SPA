#pragma once
#include "AbstractType.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace Evaluator {
    class Result {
    public:
        Result(bool resExists,
               std::unordered_map<std::string, int> syn,
               TABLE res);
        static Result merge(Result& r1, Result& r2);
        bool hasResults() const;
        std::unordered_map<std::string, int> getSynonyms() const;
        TABLE getResults() const;
    private:
        bool resultExists;
        std::unordered_map<std::string, int> synonyms;
        TABLE results;
    };
} // namespace Evaluator
