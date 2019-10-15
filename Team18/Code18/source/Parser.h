#pragma once

#include<stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "NestedResult.h"
#include "PatternProcessor.h"

using namespace std;

#include "PKB.h"

class Parser {
public:
	Parser();
	int Parse(std::string filename);
	int count(std::string s, char c);
	string parseProc(std::string line);
	string parseCall(std::string line);
	string parseRead(std::string line);
	string parsePrint(std::string line);
	string parseAssignInit(std::string line);
	vector<string> parseAssignRHS(std::string varUse);
	NestedResult parseIf(std::string ifLine, int parentStmtNo);
	NestedResult parseIfNestedInThen(std::string ifLine, int parentStmtNo);
	NestedResult parseWhile(std:: string whileLine, int parentStmtNo);
	NestedResult parseWhileNestedInThen(std::string whileLine, int parentStmtNo);
	vector<string> parseCondStmt(std::string line);
	vector<string> parseCondition(std::string condition);
	string removeOuterBrackets(std::string line);
private:
	PKB pkb;
	PatternProcessor patternProcessor;
	ifstream programFile;
	vector<NestedResult> procedures;
	NestedResult currProc;
	vector<pair<int, std::string>> callStmts;
	int nestingLevel;
	int stmtNo;
};

