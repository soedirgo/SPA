#pragma once
#include <string>
#include <vector>
#include <utility>

using namespace std;

class NestedResult {

public:
	NestedResult();
	int lastStmtNo;
	vector<string> modifiesList;
	vector<string> usesList;
	void addModifies(std::string var);
	void addUses(std::string var);
	vector<string> getModifies();
	vector<string> getUses();
};
