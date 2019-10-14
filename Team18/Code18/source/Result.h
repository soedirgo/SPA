#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "PKBHash.h"

namespace Evaluator {
    class Result {
    public:
        Result(bool resExists,
               std::unordered_map<std::string, int> syn,
               std::unordered_set<std::vector<std::string>> res);

        static Result merge(Result& r1, Result& r2);

        bool hasResults() const;
        std::unordered_map<std::string, int> getSynonyms() const;
        std::unordered_set<std::vector<std::string>> getResults() const;
    private:
        bool resultExists;
        std::unordered_map<std::string, int> synonyms;
        std::unordered_set<std::vector<std::string>> results;
    };
} // namespace Evaluator
