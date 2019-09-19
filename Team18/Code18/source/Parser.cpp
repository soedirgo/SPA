#include<stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Parser.h"
#include "PKB.h"
#include "NestedResult.h"
#include "TNode.h"
using namespace std;

Parser::Parser() {
	this ->pkb = PKB();
	this ->stmtNo = 1;
}

int Parser::Parse (string filename) {

	string line;

	//Code to open the file from the filename.
	this ->programFile.open(filename);
	if (!programFile) {
		cerr << "Unable to open file!" << filename;
	}

	while (getline(programFile, line)) {
		//Process to parse each line
		if (line.find("procedure") != string::npos) {
			string header = parseProc(line);
			//Calls PKB API to set procedure name
			pkb.setProc(header);
		}
		else if (line.find("while") != string::npos) {
			pkb.setStmt(stmtNo, While);
			NestedResult results = parseWhile(line);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setModifiesStmtByVar(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setUsesVarByStmt(stmtNo, var);
				}
			}

			stmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("if") != string::npos) {
			pkb.setStmt(stmtNo, If);
			NestedResult results = parseIf(line);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setModifiesStmtByVar(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setUsesVarByStmt(stmtNo, var);
				}
			}

			stmtNo = results.lastStmtNo + 1;
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

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setVar(var);
					pkb.setUsesVarByStmt(stmtNo, var);
				}
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
	string keyword = "procedure";
	string bracket = "{";
	//Remove all white spaces from header
	header.erase(remove_if(header.begin(), header.end(), isspace), header.end());
	//Removes procedure keyword from header
	int k = header.find(bracket);
	header.erase(k, bracket.size());
	//Removes the stmt line open bracket: { from header
	int i = header.find(keyword);
	header.erase(i, keyword.size());
	std::cout << header;
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

vector<string> Parser::parseAssignRHS(string varUse) {
	string patternRHS = varUse;
	string var = "";
	vector<string> result;
	while (patternRHS.size() > 0) {
		if (patternRHS.find("+") != string::npos) {
			int i = patternRHS.find("+");
			var = patternRHS.substr(0, i);
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		} else if (patternRHS.find("-") != string::npos) {
			int i = patternRHS.find("-");
			var = patternRHS.substr(0, i);
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		} else if (patternRHS.find("*") != string::npos) {
			int i = patternRHS.find("*");
			var = patternRHS.substr(0, i);
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		} else if (patternRHS.find("/") != string::npos) {
			int i = patternRHS.find("/");
			var = patternRHS.substr(0, i);
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		} else if (patternRHS.find("%") != string::npos) {
			int i = patternRHS.find("%");
			var = patternRHS.substr(0, i);
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		}
		else {
			var = patternRHS;
			result.push_back(var);
			break;
		}
	}
	return result;
}

NestedResult Parser::parseIf(string ifLine) {
	
	int currStmtNo = stmtNo;
	bool passedElse = false;
	NestedResult result;

	string line;

	vector<string> toAdd = parseCondStmt(ifLine);
	for (string var : toAdd) {
		result.addUses(var);
	}
	while (getline(programFile, line)) {
		//Process to parse each line
		if (line.find("while") != string::npos) {
			pkb.setStmt(stmtNo, While);
			NestedResult results = parseWhile(line);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				result.addModifies(var);
				pkb.setModifiesStmtByVar(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					result.addUses(var);
					pkb.setConstant(var);
				}
				else {
					result.addUses(var);
					pkb.setUsesVarByStmt(stmtNo, var);
				}
			}

			currStmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("if") != string::npos) {
			pkb.setStmt(stmtNo, If);
			NestedResult results = parseIf(line);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				result.addModifies(var);
				pkb.setModifiesStmtByVar(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					result.addUses(var);
					pkb.setConstant(var);
				}
				else {
					result.addUses(var);
					pkb.setUsesVarByStmt(stmtNo, var);
				}
			}

			currStmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(currStmtNo, Assign);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.setModifiesVarByStmt(currStmtNo, varMod);
			result.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setVar(var);
					pkb.setUsesVarByStmt(currStmtNo, var);
					result.addUses(var);
				}
			}

			currStmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Read);
			pkb.setModifiesVarByStmt(currStmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currStmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Print);
			pkb.setUsesVarByStmt(currStmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currStmtNo++;
		}
		else if (line.find("else") != string::npos) {
			passedElse = true;
		}
		else {
			;
		}
		if (passedElse) {
			if (line.find("}") != string::npos) {
				break;
			}
		}
	}
	result.lastStmtNo = currStmtNo;
	return result;
}

NestedResult Parser::parseWhile(string whileLine) {
	int currStmtNo = stmtNo;
	bool passedElse = false;
	NestedResult result;

	string line;

	vector<string> toAdd = parseCondStmt(whileLine);
	for (string var : toAdd) {
		result.addUses(var);
	}
	while (getline(programFile, line)) {
		//Process to parse each line
		if (line.find("while") != string::npos) {
			pkb.setStmt(stmtNo, While);
			NestedResult results = parseWhile(line);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				result.addModifies(var);
				pkb.setModifiesStmtByVar(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					result.addUses(var);
					pkb.setConstant(var);
				}
				else {
					result.addUses(var);
					pkb.setUsesVarByStmt(stmtNo, var);
				}
			}

			currStmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("if") != string::npos) {
			pkb.setStmt(stmtNo, If);
			NestedResult results = parseIf(line);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				result.addModifies(var);
				pkb.setModifiesStmtByVar(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					result.addUses(var);
					pkb.setConstant(var);
				}
				else {
					result.addUses(var);
					pkb.setUsesVarByStmt(stmtNo, var);
				}
			}

			currStmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(currStmtNo, Assign);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.setModifiesVarByStmt(currStmtNo, varMod);
			result.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setVar(var);
					pkb.setUsesVarByStmt(currStmtNo, var);
					result.addUses(var);
				}
			}

			currStmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Read);
			pkb.setModifiesVarByStmt(currStmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currStmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Print);
			pkb.setUsesVarByStmt(currStmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currStmtNo++;
		}
		else {
			;
		}
		if (passedElse) {
			if (line.find("}") != string::npos) {
				break;
			}
		}
	}
	result.lastStmtNo = currStmtNo;
	return result;
}

vector<string> Parser::parseCondStmt(string line) {
	
	regex redund = regex(R"((|))");
	regex comparitor = regex(R"(==|!=|<=|>=|<|>)");
	vector<string> result;

	int start = line.find("(") + 1;
	int end = 0;
	string temp = line;
	while (true) {
		int curr = temp.find(")");
		if (curr != string::npos) {
			end = curr;
			temp = temp.substr(curr + 1);
		}
		else {
			break;
		}
	}
	int condLen = end - start;
	string condStmt = line.substr(start, condLen);
	condStmt.erase(remove_if(condStmt.begin(), condStmt.end(), isspace), condStmt.end());
	
	while (condStmt.size() > 0) {
		if (condStmt.find("||") != string::npos || condStmt.find("&&") != string::npos) {
			int i = condStmt.find("||");
			int j = condStmt.find("&&");
			if (j == string::npos || (i != string::npos && i < j)) {
				int len = condStmt.find("||");
				string curr = condStmt.substr(0, len);
				condStmt = condStmt.substr(len + 1);
				curr = regex_replace(curr, redund, "");
				curr = regex_replace(curr, comparitor, " ");
				int split = curr.find(" ");
				string first = curr.substr(0, split);
				string second = curr.substr(split + 1);
				result.push_back(first);
				result.push_back(second);
			}
			else {
				int len = condStmt.find("&&");
				string curr = condStmt.substr(0, len);
				condStmt = condStmt.substr(len + 1);
				curr = regex_replace(curr, redund, "");
				curr = regex_replace(curr, comparitor, " ");
				int split = curr.find(" ");
				string first = curr.substr(0, split);
				string second = curr.substr(split + 1);
				result.push_back(first);
				result.push_back(second);
			}
		}
		else {
			string curr = condStmt;
			curr = regex_replace(curr, redund, "");
			curr = regex_replace(curr, comparitor, " ");
			int split = curr.find(" ");
			string first = curr.substr(0, split);
			string second = curr.substr(split + 1);
			result.push_back(first);
			result.push_back(second);
			break;
		}
	}
	return result;
}
