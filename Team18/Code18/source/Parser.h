#pragma once

#include<stdio.h>
#include <iostream>
#include <string>

using namespace std;

#include "PKB.h"

class Parser {
public:
	Parser();
	int Parse(std::string filename);
	string parseProc(std::string line);
	string parseRead(std::string line);
	string parsePrint(std::string line);
	string parseAssignInit(std::string line);
	vector<string> parseAssignRHS(std::string varUse);
	vector<string> parseIf(int stmtNo);
	vector<string> parseWhile(int stmtNo);
private:
	PKB pkb;
	int stmtNo;
};

