#pragma once
#include <string>
#include <vector>
#include <utility>

using namespace std;

class NestedResult {

public:
	NestedResult();
	string procName;
	int lastStmtNo;
	vector<string> modifiesList;
	vector<string> usesList;
	void addModifies(std::string var);
	void addUses(std::string var);
	void setProcName(std::string name);
	vector<string> getModifies();
	vector<string> getUses();
	string getProcName();
};
