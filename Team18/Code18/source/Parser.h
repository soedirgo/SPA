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
private:
	PKB pkb;
};

