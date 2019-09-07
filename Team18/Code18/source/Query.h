#pragma once
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include "Clause.h"
using namespace std;

class Query {
public:
	Query(unordered_map<string, string> declerationVariables, vector<string> selectVars,
		vector<pair<string, pair<string, string>>> suchThat);
	unordered_map<string, string> getDeclarations();
	vector<pair<string, pair<string, string>>> getSuchThatClauses();
private:
    vector<pair<string, string> > declarations;
};
