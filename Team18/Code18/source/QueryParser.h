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
	static Query parse(std::string query);

	static std::vector<std::string> findInitialDecleration(std::string query);

	static std::unordered_map<std::string, std::string> splitVariablesInDeclerations(std::vector<std::string> declerations);

	static std::string splitSelect(std::string s);

	static std::vector<std::pair<std::string, std::pair<std::string, std::string>>> splitSuchThat(std::vector<std::string> suchThat);

	static std::vector<std::pair<std::string, std::pair<std::string, std::string>>> splitPattern(std::vector<std::string> pattern);

	static std::string trim(std::string str, std::string whitespace);

	static std::string removeSpaces(std::string s, std::string whitespace);

	static std::string removeWhiteSpaces(std::string s, char whitespace);

	static int getMinimumIndex(std::vector<int> indexes);

	static std::string initialValidation(std::string query);

	static std::string declarationsValidation(std::unordered_map<std::string, std::string> declerationVariables);

	static std::string selectVariablesValidation(std::unordered_map<std::string, std::string> declerationVariables, std::string selectVars);

	static std::string suchThatValidation(std::unordered_map<std::string, std::string> declerationVariables, std::vector<std::pair<std::string, std::pair<std::string, std::string>>> suchThat);
};
