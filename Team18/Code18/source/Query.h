#pragma once
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include "Clause.h"

class Query {
public:
    Query(std::unordered_map<std::string, std::string> decl,
          std::string selectSyn,
          std::vector<Clause> clauses);
    std::unordered_map<std::string, std::string> getDeclarations();
    std::string getSelectSynonym();
    std::vector<Clause> getClauses();
private:
    std::unordered_map<std::string, std::string> declarations;
    std::string selectSyn;
    std::vector<Clause> clauses;
};
