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
	int prevStmtNo;
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
				pkb.setVar(var);
				//pkb.insertModifiesRelation(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
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
				pkb.setVar(var);
				//pkb.insertModifiesRelation(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
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
			//pkb.insertModifiesRelation(stmtNo, varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
				}
			}
			
			stmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Read);
			//pkb.insertModifiesRelation(stmtNo, readArg);
			pkb.setVar(readArg);
			stmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Print);
			//pkb.insertUsesRelation(stmtNo, printArg);
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
	int prevStmtNo = stmtNo - 1;
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
				pkb.setVar(var);
				//pkb.insertModifiesRelation(stmtNo, var);
				result.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
					result.addUses(var);
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
				pkb.setVar(var);
				//pkb.insertModifiesRelation(stmtNo, var);
				result.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
					result.addUses(var);
				}
			}

			currStmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(stmtNo, Assign);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			//pkb.insertModifiesRelation(stmtNo, varMod);
			result.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
					result.addUses(var);
				}
			}

			currStmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Read);
			//pkb.insertModifiesRelation(stmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currStmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Print);
			//pkb.insertUsesRelation(stmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currStmtNo++;
		}
		else if (line.find("else") != string::npos) {
			passedElse = true;
			continue;
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
	int prevStmtNo = stmtNo - 1;
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
				pkb.setVar(var);
				//pkb.insertModifiesRelation(stmtNo, var);
				result.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
					result.addUses(var);
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
				pkb.setVar(var);
				//pkb.insertModifiesRelation(stmtNo, var);
				result.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
					result.addUses(var);
				}
			}

			currStmtNo = results.lastStmtNo + 1;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(stmtNo, Assign);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			//pkb.insertModifiesRelation(stmtNo, varMod);
			result.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					//pkb.insertUsesRelation(stmtNo, var);
					result.addUses(var);
				}
			}

			currStmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Read);
			//pkb.insertModifiesRelation(stmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currStmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Print);
			//pkb.insertUsesRelation(stmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currStmtNo++;
		}
		else {
			;
		}
		if (line.find("}") != string::npos) {
			break;
		}
	}
	result.lastStmtNo = currStmtNo;
	return result;
}

vector<string> Parser::parseCondStmt(string line) {
	vector<string> result;
	string condStmt = line;
	condStmt.erase(remove_if(condStmt.begin(), condStmt.end(), isspace), condStmt.end());
	int start = condStmt.find("(");
	int end = condStmt.find_last_of(")");
	int condLen = end - start + 1;
	condStmt = condStmt.substr(start, condLen);

	if ((condStmt.find("||") == string::npos) && (condStmt.find("&&") == string::npos)) {
		string curr = condStmt;
		vector<string> subresult = parseCondition(curr);
		for (string var : subresult) {
			result.push_back(var);
		}
	}
	else {
		condStmt = removeOuterBrackets(condStmt);
		while (condStmt.size() > 0) {
			if ((condStmt.find("||") != string::npos) || (condStmt.find("&&") != string::npos)) {
				int i = condStmt.find("||");
				int j = condStmt.find("&&");
				if ((j == string::npos) || ((i != string::npos) && (i < j))) {
					string curr = condStmt.substr(0, i);
					condStmt = condStmt.substr(i + 2);
					vector<string> subresult = parseCondition(curr);
					for (string var : subresult) {
						result.push_back(var);
					}
				}
				else {
					string curr = condStmt.substr(0, j);
					condStmt = condStmt.substr(j + 2);
					vector<string> subresult = parseCondition(curr);
					for (string var : subresult) {
						result.push_back(var);
					}
				}
			}
			else {
				string curr = condStmt;
				vector<string> subresult = parseCondition(curr);
				for (string var : subresult) {
					result.push_back(var);
				}
				break;
			}
		}
	}
	return result;
}

string Parser:: removeOuterBrackets(string line) {
	string condStmt = line;
	condStmt = condStmt.substr(1);
	condStmt = condStmt.substr(0, condStmt.size() - 1);
	return condStmt;
}

vector<string> Parser::parseCondition(string condition) {
	vector<string> result;
	string curr = condition;
	string first;
	string second;
	curr = curr.substr(1);
	curr = curr.substr(0, curr.size() - 1);
	if (curr.find("=") != string::npos) {
		if (curr.find("==") != string::npos) {
			int i = curr.find("=");
			first = curr.substr(0, i);
			second = curr.substr(i + 2);
		}
		else {
			int i = curr.find("=");
			first = curr.substr(0, i - 1);
			second = curr.substr(i + 1);
		}
	}
	else {
		if (curr.find(">") != string::npos) {
			int i = curr.find(">");
			first = curr.substr(0, i);
			second = curr.substr(i + 1);
		}
		else {
			int i = curr.find("<");
			first = curr.substr(0, i);
			second = curr.substr(i + 1);
		}
	}
	result.push_back(first);
	result.push_back(second);
	return result;
}
