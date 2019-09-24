#pragma once
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include "Clause.h"

class Query {
public:
	Query(std::unordered_map<std::string, std::string> declarations,
		std::string selectSynonym,
		std::vector<std::pair<std::string, std::pair<std::string, std::string>>> clauses,
		std::vector<std::pair<std::string, std::pair<std::string, std::string>>> patternclauses);
	std::unordered_map<std::string, std::string> getDeclarations() const;
	std::string getSelectSynonym() const;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> getClauses() const;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> getPatternClauses() const;
    bool operator== (const Query& other) const;
private:
	std::unordered_map<std::string, std::string> declarations;
	std::string selectSynonym;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> clauses;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> patternclauses;
};
