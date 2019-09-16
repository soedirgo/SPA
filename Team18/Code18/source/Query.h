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
	std::unordered_map<std::string, std::string> getDeclarations();
	std::string getSelectSynonym();
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> getClauses();
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> getPatternClauses();
private:
	std::unordered_map<std::string, std::string> declarations;
	std::string selectSynonym;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> clauses;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> patternclauses;
};
