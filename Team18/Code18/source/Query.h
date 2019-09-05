#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Clause.h"

class Query {
public:
    Query(std::vector<std::pair<std::string, std::string> > decl,
          std::vector<Clause> clauses);
    std::vector<std::pair<std::string, std::string> > getDeclarations();
    std::vector<Clause> getClauses();
private:
    std::vector<std::pair<std::string, std::string> > declarations;
    std::vector<Clause> clauses;
};
