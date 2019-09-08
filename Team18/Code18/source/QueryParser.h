using namespace std;

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Query.h"

class QueryParser {
public:
	static string parse(string query);

	static vector<string> findInitialDecleration(string query);

	static unordered_map<string, string> splitVariablesInDeclerations(vector<string> declerations);

	static vector<string> splitSelect(string statements);

	static vector<pair<string, pair<string, string>>> splitSuchThat(vector<string> suchThat);

	//static string evalQuery(Query q);

	static string trim(string str, string whitespace);

	static string removeSpaces(string s, string whitespace);
};