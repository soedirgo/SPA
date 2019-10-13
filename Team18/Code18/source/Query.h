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
		std::vector<Clause> clauses);
	std::unordered_map<std::string, std::string> getDeclarations() const;
	std::string getSelectSynonym() const;
	std::vector<Clause> getClauses() const;
	bool operator== (const Query& other) const;
private:
	std::unordered_map<std::string, std::string> declarations;
	std::string selectSynonym;
	std::vector<Clause> clauses;
};
