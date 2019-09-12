#include<stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Parser.h"
#include "PKB.h"
#include "TNode.h"

Parser::Parser() {
	this ->pkb = PKB();
}

int Parser::Parse (string filename) {

	ifstream programFile;
	string line;
	int stmtNo = 1;
	int nestingLevel =  1;

	//Code to open the file from the filename.
	programFile.open(filename);
	if (!programFile) {
		cerr << "Unable to open file!" << filename;
	}

	while (getline(programFile, line)) {
		//Process to parse each line
		if (line.find("procedure") != string::npos) {
			string header = parseProc(line);
			//Calls PKB API to set procedure name
			//pkb.setProcName(header);
		}
		else if (line.find("while") != string::npos) {
			pkb.setStmt(stmtNo, While);
			stmtNo++;
		}
		else if (line.find("if") != string::npos) {
			pkb.setStmt(stmtNo, If);
			stmtNo++;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(stmtNo, Assign);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.setModifiesVarByStmt(stmtNo, varMod);

			string varUse = assign.substr(index + 1);

			//Condition determine if RHS is a var or const
			if (isdigit(varUse.at(0))) {
				pkb.setConstant(varUse);
			}
			else {
				pkb.setVar(varUse);
				pkb.setUsesVarByStmt(stmtNo, varUse);
			}

			stmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Read);
			pkb.setModifiesVarByStmt(stmtNo, readArg);
			pkb.setVar(readArg);
			stmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Print);
			pkb.setUsesVarByStmt(stmtNo, printArg);
			pkb.setVar(printArg);
			stmtNo++;
		}
		else {
			;
		}
	}


	return 0;
}

string Parser::parseProc(string line) {
	string header = line;
	string keyword = "Procedure";
	string bracket = "{";
	//Remove all white spaces from header
	header.erase(remove_if(header.begin(), header.end(), isspace), header.end());
	//Removes procedure keyword from header
	int k = header.find(bracket);
	header.erase(k, bracket.size());
	//Removes the stmt line open bracket: { from header
	int i = header.find(keyword);
	header.erase(i, keyword.size());

	return header;
}

string Parser::parseRead(string line) {
	string readStmt = line;
	string keyword = "read";
	//Remove all white spaces from readStmt
	readStmt.erase(remove_if(readStmt.begin(), readStmt.end(), isspace), readStmt.end());
	//Removes read keyword from readStmt
	int i = readStmt.find(keyword);
	readStmt.erase(i, keyword.size());
	//Removes ; from readStmt
	readStmt.erase(readStmt.size() - 1);

	return readStmt;
}

string Parser::parsePrint(string line) {
	string printStmt = line;
	string keyword = "print";
	//Remove all white spaces from printStmt
	printStmt.erase(remove_if(printStmt.begin(), printStmt.end(), isspace), printStmt.end());
	//Removes print keyword from printStmt
	int i = printStmt.find(keyword);
	printStmt.erase(i, keyword.size());
	//Removes ; from print statement
	printStmt.erase(printStmt.size() - 1);

	return printStmt;
}

string Parser::parseAssignInit(string line) {
	string assign = line;
	//Remove all white spaces from assign
	assign.erase(remove_if(assign.begin(), assign.end(), isspace), assign.end());
	//Removes ; from assign
	assign.erase(assign.size() - 1);

	return assign;
}

