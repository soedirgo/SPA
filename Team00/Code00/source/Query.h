#pragma once
#include <string>

class Query {
public:
    string getType();
    string getClause();
    Query(string type, string clause);
private:
    // could be declaration or select. maybe use enum?
    string type;
    // "such that" clause (if any, could be none: point to nullptr)
    string clause;
};
