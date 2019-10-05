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
	this->nestingLevel = 0;
	this->currProc = NestedResult();
}

int Parser::Parse (string filename) {

	string line;
	int prevStmtNo = 0;
	//Code to open the file from the filename.
	this ->programFile.open(filename);
	if (!programFile) {
		cerr << "Unable to open file!" << filename;
	}

	while (getline(programFile, line)) {

		if (count(line, ';') > 1) {
			throw stmtNo;
		}
		//Process to parse each line
		if (line.find("procedure") != string::npos) {
			if (stmtNo != 1) {
				procedures.push_back(currProc);
				currProc = NestedResult();
			}
			string header = parseProc(line);
			//Calls PKB API to set procedure name
			currProc.setProcName(header);
			pkb.setProc(header);
		}
		else if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(stmtNo, While);
			nestingLevel++;
			NestedResult results = parseWhile(line, stmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				currProc.addModifies(var);
				pkb.insertModifiesRelation(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, stmtNo);
				}
				else {
					pkb.setVar(var);
					currProc.addModifies(var);
					pkb.insertUsesRelation(stmtNo, var);
				}
			}
			if (stmtNo != 1) {
				pkb.insertFollowRelation(prevStmtNo, stmtNo);
			}
			prevStmtNo = stmtNo;
			stmtNo = results.lastStmtNo;
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(stmtNo, If);
			nestingLevel++;
			NestedResult results = parseIf(line, stmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				currProc.addModifies(var);
				pkb.insertModifiesRelation(stmtNo, var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, stmtNo);
				}
				else {
					pkb.setVar(var);
					currProc.addUses(var);
					pkb.insertUsesRelation(stmtNo, var);
				}
			}

			if (stmtNo != 1) {
				pkb.insertFollowRelation(prevStmtNo, stmtNo);
			}
			prevStmtNo = stmtNo;
			stmtNo = results.lastStmtNo;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(stmtNo, Assign);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.insertModifiesRelation(stmtNo, varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);
			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, stmtNo);
				}
				else {
					pkb.setVar(var);
					currProc.addUses(var);
					pkb.insertUsesRelation(stmtNo, var);
				}
			}

			if (stmtNo != 1) {
				pkb.insertFollowRelation(prevStmtNo, stmtNo);
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Read);
			pkb.insertModifiesRelation(stmtNo, readArg);
			pkb.setVar(readArg);
			currProc.addModifies(readArg);
			
			if (stmtNo != 1) {
				pkb.insertFollowRelation(prevStmtNo, stmtNo);
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(stmtNo, Print);
			pkb.insertUsesRelation(stmtNo, printArg);
			pkb.setVar(printArg);
			currProc.addUses(printArg);
			
			if (stmtNo != 1) {
				pkb.insertFollowRelation(prevStmtNo, stmtNo);
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else if (line.find("call") != string::npos) {
			string proc = parseCall(line);
			//pkb.setStmt(stmtNo, Call);
			callStmts.push_back(make_pair(stmtNo, proc));
			if (stmtNo != 1) {
				pkb.insertFollowRelation(prevStmtNo, stmtNo);
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else {
			;
		}

		for (NestedResult proc : procedures) {
			string procName = proc.getProcName();
			for (string var : proc.getModifies()) {
				//pkb.insertProcModifiesRelation(procName, var);
			}
			for (string var : proc.getUses()) {
				//pkb.insertProcUsesRelation(procName, var);
			}
		}

		for (pair<int, std::string> call : callStmts) {
			int stmtNo = call.first;
			string procName = call.second;
			for (NestedResult proc : procedures) {
				if (proc.getProcName() == procName) {
					for (string var : proc.getModifies()) {
						pkb.insertModifiesRelation(stmtNo, var);
					}
					for (string var : proc.getUses()) {
						pkb.insertUsesRelation(stmtNo, var);
					}
				}
			}
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
	return header;
}

string Parser::parseCall(string line) {
	string header = line;
	string keyword = "call";
	header.erase(remove_if(header.begin(), header.end(), isspace), header.end());
	header.erase(std::remove(header.begin(), header.end(), '}'), header.end());
	header.erase(std::remove(header.begin(), header.end(), ';'), header.end());
	int i = header.find(keyword);
	header.erase(i, keyword.size());
	return header;
}

string Parser::parseRead(string line) {
	string readStmt = line;
	string keyword = "read";
	//Remove all white spaces from readStmt
	readStmt.erase(remove_if(readStmt.begin(), readStmt.end(), isspace), readStmt.end());
	readStmt.erase(std::remove(readStmt.begin(), readStmt.end(), '}'), readStmt.end());
	//Removes read keyword from readStmt
	int i = readStmt.find(keyword);
	readStmt.erase(i, keyword.size());
	//Removes ; from readStmt
	readStmt.erase(std::remove(readStmt.begin(), readStmt.end(), ';'), readStmt.end());

	return readStmt;
}

string Parser::parsePrint(string line) {
	string printStmt = line;
	string keyword = "print";
	//Remove all white spaces from printStmt
	printStmt.erase(remove_if(printStmt.begin(), printStmt.end(), isspace), printStmt.end());
	printStmt.erase(std::remove(printStmt.begin(), printStmt.end(), '}'), printStmt.end());
	//Removes print keyword from printStmt
	int i = printStmt.find(keyword);
	printStmt.erase(i, keyword.size());
	//Removes ; from print statement
	printStmt.erase(std::remove(printStmt.begin(), printStmt.end(), ';'), printStmt.end());

	return printStmt;
}

string Parser::parseAssignInit(string line) {
	string assign = line;
	//Remove all white spaces from assign
	assign.erase(remove_if(assign.begin(), assign.end(), isspace), assign.end());
	assign.erase(std::remove(assign.begin(), assign.end(), '}'), assign.end());
	//Removes ; from assign
	assign.erase(std::remove(assign.begin(), assign.end(), ';'), assign.end());

	return assign;
}

vector<string> Parser::parseAssignRHS(string varUse) {
	string patternRHS = varUse;
	patternRHS.erase(std::remove(patternRHS.begin(), patternRHS.end(), ')'), patternRHS.end());
	patternRHS.erase(std::remove(patternRHS.begin(), patternRHS.end(), '('), patternRHS.end());
	string var = "";
	vector<string> result;
	int i = 999;
	while (patternRHS.size() > 0) {
		i = 999;
		if (patternRHS.find("+") != string::npos || patternRHS.find("-") != string::npos || patternRHS.find("*") != string::npos || 
			patternRHS.find("/") != string::npos || patternRHS.find("%") != string::npos) {
			if (patternRHS.find("+") != string::npos) {
				if (patternRHS.find("+") < i) {
					i = patternRHS.find("+");
				}
			}
			if (patternRHS.find("-") != string::npos) {
				if (patternRHS.find("-") < i) {
					i = patternRHS.find("-");
				}
			}
			if (patternRHS.find("*") != string::npos) {
				if (patternRHS.find("*") < i) {
					i = patternRHS.find("*");
				}
			}
			if (patternRHS.find("%") != string::npos) {
				if (patternRHS.find("%") < i) {
					i = patternRHS.find("%");
				}
			}
			if (patternRHS.find("/") != string::npos) {
				if (patternRHS.find("/") < i) {
					i = patternRHS.find("/");
				}
			}
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

NestedResult Parser::parseIf(string ifLine, int parentStmtNo) {
	
	int currStmtNo = parentStmtNo + 1;
	int startStmtNo = parentStmtNo;
	int elseStmtNo = 0;
	int prevStmtNo = parentStmtNo;
	bool passedElse = false;
	int currNestingLevel = nestingLevel;
	NestedResult result;

	string line;

	vector<string> toAdd = parseCondStmt(ifLine);
	for (string var : toAdd) {
		result.addUses(var);
	}
	while (getline(programFile, line)) {
		if (count(line, ';') > 1) {
			throw currStmtNo;
		}
		//Process to parse each line
		if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, While);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results;
			if (passedElse) {
				results = parseWhile(line, currStmtNo);
			}
			else {
				results = parseWhileNestedInThen(line, currStmtNo);
			}
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, If);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results;
			if (passedElse) {
				results = parseIf(line, currStmtNo);
			}
			else {
				results = parseIfNestedInThen(line, currStmtNo);
			}
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = line;
			if (assign.find("}") != string::npos && passedElse) {
				nestingLevel = nestingLevel - count(line, '}');
				assign.erase(std::remove(assign.begin(), assign.end(), '}'), assign.end());
			}
			assign = parseAssignInit(line);
			pkb.setStmt(currStmtNo, Assign);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.insertModifiesRelation(currStmtNo, varMod);
			result.addModifies(varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = line;
			if (readArg.find("}") != string::npos && passedElse) {
				nestingLevel = nestingLevel - count(readArg, '}');
				readArg.erase(std::remove(readArg.begin(), readArg.end(), '}'), readArg.end());
			}
			readArg = parseRead(readArg);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Read);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertModifiesRelation(currStmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currProc.addModifies(readArg);

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = line;
			if (printArg.find("}") != string::npos && passedElse) {
				nestingLevel = nestingLevel - count(printArg, '}');
				printArg.erase(std::remove(printArg.begin(), printArg.end(), '}'), printArg.end());
			}
			printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Print);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertUsesRelation(currStmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currProc.addUses(printArg);

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("call") != string::npos) {
		string proc = parseCall(line);
		//pkb.setStmt(stmtNo, Call);
		callStmts.push_back(make_pair(stmtNo, proc));
		if (stmtNo != 1) {
			pkb.insertFollowRelation(prevStmtNo, stmtNo);
		}
		prevStmtNo = currStmtNo;
		currStmtNo++;
		}
		else if (line.find("else") != string::npos) {
			passedElse = true;
			elseStmtNo = currStmtNo;
			continue;
		}
		else {
			if (passedElse) {
				if (line.find("}") != string::npos) {
					nestingLevel--;
					break;
				}
			}
		}
	}
	result.lastStmtNo = currStmtNo;
	return result;
}

NestedResult Parser::parseIfNestedInThen(string ifLine, int parentStmtNo) {

	int currStmtNo = parentStmtNo + 1;
	int startStmtNo = parentStmtNo;
	int elseStmtNo = 0;
	int prevStmtNo = parentStmtNo;
	bool passedElse = false;
	int currNestingLevel = nestingLevel;
	NestedResult result;

	string line;

	vector<string> toAdd = parseCondStmt(ifLine);
	for (string var : toAdd) {
		result.addUses(var);
	}
	while (getline(programFile, line)) {
		if (count(line, ';') > 1) {
			throw currStmtNo;
		}
		//Process to parse each line
		if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, While);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results;
			if (passedElse) {
				results = parseWhile(line, currStmtNo);
			}
			else {
				results = parseWhileNestedInThen(line, currStmtNo);
			}
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, If);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results;
			if (passedElse) {
				results = parseIf(line, currStmtNo);
			}
			else {
				results = parseIfNestedInThen(line, currStmtNo);
			}
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = line;
			if (assign.find("}") != string::npos && passedElse) {
				nestingLevel = nestingLevel - 1;
				assign.erase(std::remove(assign.begin(), assign.end(), '}'), assign.end());
			}
			assign = parseAssignInit(line);
			pkb.setStmt(currStmtNo, Assign);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.insertModifiesRelation(currStmtNo, varMod);
			result.addModifies(varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = line;
			if (readArg.find("}") != string::npos && passedElse) {
				nestingLevel = nestingLevel - 1;
				readArg.erase(std::remove(readArg.begin(), readArg.end(), '}'), readArg.end());
			}
			readArg = parseRead(readArg);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Read);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertModifiesRelation(currStmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currProc.addModifies(readArg);

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = line;
			if (printArg.find("}") != string::npos && passedElse) {
				nestingLevel = nestingLevel - 1;
				printArg.erase(std::remove(printArg.begin(), printArg.end(), '}'), printArg.end());
			}
			printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Print);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertUsesRelation(currStmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currProc.addUses(printArg);

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.insertFollowRelation(prevStmtNo, currStmtNo);
					}
				}
				else {
					pkb.insertFollowRelation(prevStmtNo, currStmtNo);
				}
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("call") != string::npos) {
		string proc = parseCall(line);
		//pkb.setStmt(stmtNo, Call);
		callStmts.push_back(make_pair(stmtNo, proc));
		if (stmtNo != 1) {
			pkb.insertFollowRelation(prevStmtNo, stmtNo);
		}
		prevStmtNo = currStmtNo;
		currStmtNo++;
		}
		else if (line.find("else") != string::npos) {
			passedElse = true;
			elseStmtNo = currStmtNo;
			continue;
		}
		else {
			if (passedElse) {
				if (line.find("}") != string::npos) {
					nestingLevel--;
					break;
				}
			}
		}
	}
	result.lastStmtNo = currStmtNo;
	return result;
}


NestedResult Parser::parseWhileNestedInThen(string whileLine, int parentStmtNo) {
	int currStmtNo = parentStmtNo + 1;
	int startStmtNo = parentStmtNo;
	int prevStmtNo = parentStmtNo;
	int currNestingLevel = nestingLevel;
	NestedResult result;

	string line;

	vector<string> toAdd = parseCondStmt(whileLine);
	for (string var : toAdd) {
		result.addUses(var);
	}
	while (getline(programFile, line)) {
		if (count(line, ';') > 1) {
			throw currStmtNo;
		}
		//Process to parse each line
		if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, While);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results = parseWhile(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, If);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results = parseIf(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = line;
			if (assign.find("}") != string::npos) {
				nestingLevel = nestingLevel - 1;
				assign.erase(std::remove(assign.begin(), assign.end(), '}'), assign.end());
			}
			assign = parseAssignInit(line);
			pkb.setStmt(currStmtNo, Assign);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.insertModifiesRelation(currStmtNo, varMod);
			result.addModifies(varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);
			
			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = line;
			if (readArg.find("}") != string::npos) {
				nestingLevel = nestingLevel - 1;
				readArg.erase(std::remove(readArg.begin(), readArg.end(), '}'), readArg.end());
			}
			readArg = parseRead(readArg);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Read);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertModifiesRelation(currStmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currProc.addModifies(readArg);

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = line;
			if (printArg.find("}") != string::npos) {
				nestingLevel = nestingLevel - 1;
				printArg.erase(std::remove(printArg.begin(), printArg.end(), '}'), printArg.end());
			}
			printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Print);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertUsesRelation(currStmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currProc.addUses(printArg);

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("call") != string::npos) {
		string proc = parseCall(line);
		//pkb.setStmt(stmtNo, Call);
		callStmts.push_back(make_pair(stmtNo, proc));
		if (stmtNo != 1) {
			pkb.insertFollowRelation(prevStmtNo, stmtNo);
		}
		prevStmtNo = currStmtNo;
		currStmtNo++;
		}
		else {
			if (line.find("}") != string::npos) {
				nestingLevel--;
				break;
			}
		}
	}
	result.lastStmtNo = currStmtNo;
	return result;
}

NestedResult Parser::parseWhile(string whileLine, int parentStmtNo) {
	int currStmtNo = parentStmtNo + 1;
	int startStmtNo = parentStmtNo;
	int prevStmtNo = parentStmtNo;
	int currNestingLevel = nestingLevel;
	NestedResult result;

	string line;

	vector<string> toAdd = parseCondStmt(whileLine);
	for (string var : toAdd) {
		result.addUses(var);
	}
	while (getline(programFile, line)) {
		if (count(line, ';') > 1) {
			throw currStmtNo;
		}
		//Process to parse each line
		if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, While);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results = parseWhile(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(currStmtNo, If);
			pkb.insertParentRelation(startStmtNo, currStmtNo);
			nestingLevel++;
			NestedResult results = parseIf(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			for (string var : modifies) {
				pkb.setVar(var);
				pkb.insertModifiesRelation(currStmtNo, var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = line;
			if (assign.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(line, '}');
				assign.erase(std::remove(assign.begin(), assign.end(), '}'), assign.end());
			}
			assign = parseAssignInit(line);
			pkb.setStmt(currStmtNo, Assign);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			pkb.setVar(varMod);
			pkb.insertModifiesRelation(currStmtNo, varMod);
			result.addModifies(varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);
			
			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(var, currStmtNo);
					result.addUses(var);
				}
				else {
					pkb.setVar(var);
					pkb.insertUsesRelation(currStmtNo, var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = line;
			if (readArg.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(readArg, '}');
				readArg.erase(std::remove(readArg.begin(), readArg.end(), '}'), readArg.end());
			}
			readArg = parseRead(readArg);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Read);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertModifiesRelation(currStmtNo, readArg);
			pkb.setVar(readArg);
			result.addModifies(readArg);
			currProc.addModifies(readArg);

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = line;
			if (printArg.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(printArg, '}');
				printArg.erase(std::remove(printArg.begin(), printArg.end(), '}'), printArg.end());
			}
			printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(currStmtNo, Print);
			pkb.insertParentRelation(startStmtNo, currStmtNo);

			pkb.insertUsesRelation(currStmtNo, printArg);
			pkb.setVar(printArg);
			result.addUses(printArg);
			currProc.addUses(printArg);

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.insertFollowRelation(prevStmtNo, currStmtNo);
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel != currNestingLevel) {
				break;
			}
		}
		else if (line.find("call") != string::npos) {
		string proc = parseCall(line);
		//pkb.setStmt(stmtNo, Call);
		callStmts.push_back(make_pair(stmtNo, proc));
		if (stmtNo != 1) {
			pkb.insertFollowRelation(prevStmtNo, stmtNo);
		}
		prevStmtNo = currStmtNo;
		currStmtNo++;
		}
		else {
			if (line.find("}") != string::npos) {
				nestingLevel--;
				break;
			}
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
			if (var.find('!') != string::npos) {
				var = var.substr(1);
			}
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
						if (var.find('!') != string::npos) {
							var = var.substr(1);
						}
						result.push_back(var);
					}
				}
				else {
					string curr = condStmt.substr(0, j);
					condStmt = condStmt.substr(j + 2);
					vector<string> subresult = parseCondition(curr);
					for (string var : subresult) {
						if (var.find('!') != string::npos) {
							var = var.substr(1);
						}
						result.push_back(var);
					}
				}
			}
			else {
				string curr = condStmt;
				vector<string> subresult = parseCondition(curr);
				for (string var : subresult) {
					if (var.find('!') != string::npos) {
						var = var.substr(1);
					}
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
	
	vector<string> subresultFirst = parseAssignRHS(first);
	for (string element : subresultFirst) {
		result.push_back(element);
	}
	
	vector<string> subresultSecond = parseAssignRHS(second);
	for (string element : subresultSecond) {
		result.push_back(element);
	}
	return result;
}

int Parser::count(string s, char c) {
	// Count variable 
	int res = 0;

	for (int i = 0; i < s.length(); i++)

		// checking character in string 
		if (s[i] == c)
			res++;

	return res;
}
