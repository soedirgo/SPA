#pragma once

#include<stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "NestedResult.h"

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
	NestedResult parseIf(std::string ifLine);
	NestedResult parseWhile(std:: string whileLine);
	vector<string> parseCondStmt(std::string line);
private:
	PKB pkb;
	ifstream programFile;
	int stmtNo;
};

