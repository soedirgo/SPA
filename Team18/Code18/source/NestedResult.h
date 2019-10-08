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
	vector<string> condExprList;
	vector<string> callList;
	void addModifies(std::string var);
	void addUses(std::string var);
	void addCondExpr(std::string var);
	void addCalls(std::string proc);
	void setProcName(std::string name);
	vector<string> getModifies();
	vector<string> getUses();
	vector<string> getCondExpr();
	vector<string> getCallList();
	string getProcName();
};
