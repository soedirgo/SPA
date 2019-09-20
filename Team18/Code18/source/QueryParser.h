#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Query.h"
#include "Clause.h"

class QueryParser {
public:
	static std::list<std::string> parse(std::string query);

	static std::vector<std::string> findInitialDecleration(std::string query);

	static std::unordered_map<std::string, std::string> splitVariablesInDeclerations(std::vector<std::string> declerations);

	static std::string splitSelect(std::string statements);

	static std::vector<std::pair<std::string, std::pair<std::string, std::string>>> splitSuchThat(std::vector<std::string> suchThat);

	static std::vector<std::pair<std::string, std::pair<std::string, std::string>>> splitPattern(std::vector<std::string> pattern);

	static std::list<std::string> evalQuery(Query q);

	static std::string trim(std::string str, std::string whitespace);

	static std::string removeSpaces(std::string s, std::string whitespace);

	static int getMinimumIndex(std::vector<int> indexes);
};
