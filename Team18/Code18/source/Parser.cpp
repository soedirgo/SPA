#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Parser.h"
#include "PKB.h"
#include "PKBParent.h"
#include "NestedResult.h"

using namespace std;

Parser::Parser() {
	this->pkb = PKB();
	this->patternProcessor = PatternProcessor();
	this->stmtNo = 1;
	this->nestingLevel = 0;
	this->name = "^([a-zA-Z])([a-zA-Z0-9])*";
	this->number = "^([0-9])*";
	this->currProc = NestedResult();
}

int Parser::Parse(string filename) {

	string line;
	int prevStmtNo = 0;

	bool prevIf = false;
	bool prevWhile = false;
	vector<int> prevIfStmtNo;
	int prevWhileStmtNo = 0;
	int startStmtNo = 1;

	//Code to open the file from the filename.
	this->programFile.open(filename);
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
				startStmtNo = stmtNo;
				prevIf = false;
				prevWhile = false;
			}
			string header = parseProc(line);
			if (!(regex_match(header, name))) {
				throw stmtNo;
			}
			//Calls PKB API to set procedure name
			currProc.setProcName(header);
			pkb.setProcedure(header);
		}
		else if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(to_string(stmtNo), "while");
			nestingLevel++;
			NestedResult results = parseWhile(line, stmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			int prevStmt = results.getPrevWhileStmt();

			for (string var : modifies) {
				pkb.setVariable(var);
				currProc.addModifies(var);
				pkb.setModifiesS(to_string(stmtNo), var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(stmtNo),var);
				}
				else {
					pkb.setVariable(var);
					currProc.addUses(var);
					pkb.setUsesS(to_string(stmtNo), var);
				}
			}

			vector<string> condExpr = results.getCondExpr();
			for (string var : condExpr) {
				pkb.setWhilePattern(to_string(stmtNo), var);
			}
			if (stmtNo != startStmtNo) {
				pkb.setFollows(to_string(prevStmtNo), to_string(stmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(stmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(stmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(stmtNo));
				}
			}
			prevWhile = true;
			prevWhileStmtNo = prevStmt;
			prevStmtNo = stmtNo;
			stmtNo = results.lastStmtNo;
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(to_string(stmtNo), "if");
			nestingLevel++;
			NestedResult results = parseIf(line, stmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			vector<int> prevStmts = results.getPrevIfStmt();

			for (string var : modifies) {
				pkb.setVariable(var);
				currProc.addModifies(var);
				pkb.setModifiesS(to_string(stmtNo), var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(stmtNo),var);
				}
				else {
					pkb.setVariable(var);
					currProc.addUses(var);
					pkb.setUsesS(to_string(stmtNo), var);
				}
			}

			vector<string> condExpr = results.getCondExpr();
			for (string var : condExpr) {
				pkb.setIfPattern(to_string(stmtNo), var);
			}
			if (stmtNo != startStmtNo) {
				pkb.setFollows(to_string(prevStmtNo), to_string(stmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(stmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(stmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(stmtNo));
				}
			}
			prevIf = true;
			prevIfStmtNo = prevStmts;
			prevStmtNo = stmtNo;
			stmtNo = results.lastStmtNo;
		}
		else if (line.find("=") != string::npos) {
			//Initial processing of stmt
			string assign = parseAssignInit(line);
			pkb.setStmt(to_string(stmtNo), "assign");

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			if (!(regex_match(varMod, name))) {
				throw stmtNo;
			}
			pkb.setVariable(varMod);
			pkb.setModifiesS(to_string(stmtNo), varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);
			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);
			string pattern = patternProcessor.infixtoRPNexpression(varUse);
			pkb.setAssignPattern(to_string(stmtNo), pattern);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(stmtNo),var);
				}
				else {
					pkb.setVariable(var);
					currProc.addUses(var);
					pkb.setUsesS(to_string(stmtNo), var);
				}
			}

			if (stmtNo != startStmtNo) {
				pkb.setFollows(to_string(prevStmtNo), to_string(stmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(stmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(stmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(stmtNo));
				}
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else if (line.find("read") != string::npos) {
			//Gets the variable used in read stmt into readArg
			string readArg = parseRead(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(to_string(stmtNo), "read");
			pkb.setRead(readArg);
			pkb.setModifiesS(to_string(stmtNo), readArg);
			pkb.setVariable(readArg);
			currProc.addModifies(readArg);

			if (stmtNo != startStmtNo) {
				pkb.setFollows(to_string(prevStmtNo), to_string(stmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(stmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(stmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(stmtNo));
				}
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else if (line.find("print") != string::npos) {
			//Gets the variable used in print stmt into printArg
			string printArg = parsePrint(line);
			//Sets stmt information in PKB and then sets modifies variable for that stmt
			pkb.setStmt(to_string(stmtNo), "print");
			pkb.setPrint(printArg);
			pkb.setUsesS(to_string(stmtNo), printArg);
			pkb.setVariable(printArg);
			currProc.addUses(printArg);

			if (stmtNo != startStmtNo) {
				pkb.setFollows(to_string(prevStmtNo), to_string(stmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(stmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(stmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(stmtNo));
				}
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else if (line.find("call") != string::npos) {
			string proc = parseCall(line);
			pkb.setStmt(to_string(stmtNo), "call");
			pkb.setCallStmt(to_string(stmtNo), proc);
			pkb.setCallProc(currProc.getProcName(), proc);
			callStmts.push_back(make_pair(stmtNo, proc));
			currProc.addCalls(proc);
			if (stmtNo != startStmtNo) {
				pkb.setFollows(to_string(prevStmtNo), to_string(stmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(stmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(stmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(stmtNo));
				}
			}
			prevStmtNo = stmtNo;
			stmtNo++;
		}
		else {
			;
		}
	}
	procedures.push_back(currProc);
	/*
	//sets all the uses and modifies from the calls statements (brute force now - to be changed to a topo-sort algorithm)
	for (NestedResult proc : procedures) {
		string procName = proc.getProcName();
		vector<string> calls = proc.getCallList();
		for (int i = 0; i < procedures.size(); i++) {
			for (string call : calls) {
				for (NestedResult procedure : procedures) {
					if (procedure.getProcName() == call) {
						for (string var : procedure.getModifies()) {
							proc.addModifies(var);
						}
						for (string var : procedure.getUses()) {
							proc.addUses(var);
						}
					}
				}
			}
		}
	}

	for (pair<int, std::string> call : callStmts) {
		int stmtNo = call.first;
		string procName = call.second;
		for (NestedResult proc : procedures) {
			if (proc.getProcName() == procName) {
				for (string var : proc.getModifies()) {
					int currStmtNo = stmtNo;
					pkb.setModifiesS(to_string(stmtNo), var);
					while (PKB::isParentExist(to_string(currStmtNo))) {
						currStmtNo = stoi(PKB::getParentStmt(to_string(currStmtNo)));
						pkb.setModifiesS(to_string(currStmtNo), var);
					}
				}
				for (string var : proc.getUses()) {
					int currStmtNo = stmtNo;
					pkb.setUsesS(to_string(stmtNo), var);
					while (PKB::isParentExist(to_string(currStmtNo))) {
						currStmtNo = stoi(PKB::getParentStmt(to_string(currStmtNo)));
						pkb.setUsesS(to_string(currStmtNo), var);
					}
				}
			}
		}
	}
	*/

	for (NestedResult proc : procedures) {
		string procName = proc.getProcName();
		for (string var : proc.getModifies()) {
			pkb.setModifiesP(procName, var);
		}
		for (string var : proc.getUses()) {
			pkb.setUsesP(procName, var);
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
	if (!regex_match(header,name)) {
		throw stmtNo;
	}
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
	if (!regex_match(header, name)) {
		throw stmtNo;
	}
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
	if (!regex_match(readStmt, name)) {
		throw stmtNo;
	}
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
	if (!regex_match(printStmt, name)) {
		throw stmtNo;
	}
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
	int i = INT_MAX;
	while (patternRHS.size() > 0) {
		i = INT_MAX;
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
			if (!(regex_match(var, name) || regex_match(var, number))) {
				throw stmtNo;
			}
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		}
		else {
			var = patternRHS;
			if (!(regex_match(var, name) || regex_match(var, number))) {
				throw stmtNo;
			}
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
	nestingLevel++;
	NestedResult result;

	bool prevIf = false;
	bool prevWhile = false;
	vector<int> prevIfStmtNo;
	int prevWhileStmtNo = 0;

	string line;

	vector<string> toAdd = parseCondStmt(ifLine);
	for (string var : toAdd) {
		result.addUses(var);
		if (!isdigit(var.at(0))) {
			currProc.addUses(var);
			result.addCondExpr(var);
		}
	}
	while (getline(programFile, line)) {
		if (count(line, ';') > 1) {
			throw currStmtNo;
		}
		//Process to parse each line
		if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(to_string(currStmtNo), "while");
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));
			nestingLevel++;
			NestedResult results;
			results = parseWhile(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			int stmt = results.getPrevWhileStmt();
			for (string var : modifies) {
				pkb.setVariable(var);
				pkb.setModifiesS(to_string(currStmtNo), var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(currStmtNo),var);
					result.addUses(var);
				}
				else {
					pkb.setVariable(var);
					pkb.setUsesS(to_string(currStmtNo), var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			vector<string> condExpr = results.getCondExpr();
			for (string var : condExpr) {
				pkb.setWhilePattern(to_string(currStmtNo), var);
			}
			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
						if (prevIf) {
							for (int stmt : prevIfStmtNo) {
								pkb.setNext(to_string(stmt), to_string(currStmtNo));
							}
							prevIf = false;
						}
						else if (prevWhile) {
							pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
							prevWhile = false;
						}
						else {
							pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
						}
					}
					else {
						pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
					}
				}
				else {
					pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
					if (prevIf) {
						for (int stmt : prevIfStmtNo) {
							pkb.setNext(to_string(stmt), to_string(currStmtNo));
						}
						prevIf = false;
					}
					else if (prevWhile) {
						pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
						prevWhile = false;
					}
					else {
						pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
					}
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}

			prevWhile = true;
			prevWhileStmtNo = stmt;
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(to_string(currStmtNo), "if");
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));
			nestingLevel++;
			NestedResult results;
			results = parseIf(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			vector<int> stmt = results.getPrevIfStmt();
			for (string var : modifies) {
				pkb.setVariable(var);
				pkb.setModifiesS(to_string(currStmtNo), var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(currStmtNo),var);
					result.addUses(var);
				}
				else {
					pkb.setVariable(var);
					pkb.setUsesS(to_string(currStmtNo), var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			vector<string> condExpr = results.getCondExpr();
			for (string var : condExpr) {
				pkb.setIfPattern(to_string(currStmtNo), var);
			}
			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
						if (prevIf) {
							for (int stmt : prevIfStmtNo) {
								pkb.setNext(to_string(stmt), to_string(currStmtNo));
							}
							prevIf = false;
						}
						else if (prevWhile) {
							pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
							prevWhile = false;
						}
						else {
							pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
						}
					}
					else {
						pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
					}
				}
				else {
					pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
					if (prevIf) {
						for (int stmt : prevIfStmtNo) {
							pkb.setNext(to_string(stmt), to_string(currStmtNo));
						}
						prevIf = false;
					}
					else if (prevWhile) {
						pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
						prevWhile = false;
					}
					else {
						pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
					}
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}

			prevIf = true;
			prevIfStmtNo = stmt;
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel < currNestingLevel) {
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
			pkb.setStmt(to_string(currStmtNo), "assign");
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			if (!(regex_match(varMod, name))) {
				throw stmtNo;
			}
			pkb.setVariable(varMod);
			pkb.setModifiesS(to_string(currStmtNo), varMod);
			result.addModifies(varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);
			string pattern = patternProcessor.infixtoRPNexpression(varUse);
			pkb.setAssignPattern(to_string(currStmtNo), pattern);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(currStmtNo),var);
					result.addUses(var);
				}
				else {
					pkb.setVariable(var);
					pkb.setUsesS(to_string(currStmtNo), var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
						if (prevIf) {
							for (int stmt : prevIfStmtNo) {
								pkb.setNext(to_string(stmt), to_string(currStmtNo));
							}
							prevIf = false;
						}
						else if (prevWhile) {
							pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
							prevWhile = false;
						}
						else {
							pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
						}
					}
					else {
						pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
					}
				}
				else {
					pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
					if (prevIf) {
						for (int stmt : prevIfStmtNo) {
							pkb.setNext(to_string(stmt), to_string(currStmtNo));
						}
						prevIf = false;
					}
					else if (prevWhile) {
						pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
						prevWhile = false;
					}
					else {
						pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
					}
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
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
			pkb.setStmt(to_string(currStmtNo), "read");
			pkb.setRead(readArg);
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));

			pkb.setModifiesS(to_string(currStmtNo), readArg);
			pkb.setVariable(readArg);
			result.addModifies(readArg);
			currProc.addModifies(readArg);

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
						if (prevIf) {
							for (int stmt : prevIfStmtNo) {
								pkb.setNext(to_string(stmt), to_string(currStmtNo));
							}
							prevIf = false;
						}
						else if (prevWhile) {
							pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
							prevWhile = false;
						}
						else {
							pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
						}
					}
					else {
						pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
					}
				}
				else {
					pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
					if (prevIf) {
						for (int stmt : prevIfStmtNo) {
							pkb.setNext(to_string(stmt), to_string(currStmtNo));
						}
						prevIf = false;
					}
					else if (prevWhile) {
						pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
						prevWhile = false;
					}
					else {
						pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
					}
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
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
			pkb.setStmt(to_string(currStmtNo), "print");
			pkb.setPrint(printArg);
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));

			pkb.setUsesS(to_string(currStmtNo), printArg);
			pkb.setVariable(printArg);
			result.addUses(printArg);
			currProc.addUses(printArg);

			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
						if (prevIf) {
							for (int stmt : prevIfStmtNo) {
								pkb.setNext(to_string(stmt), to_string(currStmtNo));
							}
							prevIf = false;
						}
						else if (prevWhile) {
							pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
							prevWhile = false;
						}
						else {
							pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
						}
					}
					else {
						pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
					}
				}
				else {
					pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
					if (prevIf) {
						for (int stmt : prevIfStmtNo) {
							pkb.setNext(to_string(stmt), to_string(currStmtNo));
						}
						prevIf = false;
					}
					else if (prevWhile) {
						pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
						prevWhile = false;
					}
					else {
						pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
					}
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
		else if (line.find("call") != string::npos) {
			string callArg = line;
			if (callArg.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(line, '}');
				callArg.erase(std::remove(callArg.begin(), callArg.end(), '}'), callArg.end());
			}
			string proc = parseCall(callArg);
			pkb.setStmt(to_string(currStmtNo), "call");
			pkb.setCallStmt(to_string(currStmtNo), proc);
			pkb.setCallProc(currProc.getProcName(), proc);
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));
			callStmts.push_back(make_pair(currStmtNo, proc));
			currProc.addCalls(proc);
			if (currStmtNo != (startStmtNo + 1)) {
				if (passedElse) {
					if (currStmtNo != elseStmtNo) {
						pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
						if (prevIf) {
							for (int stmt : prevIfStmtNo) {
								pkb.setNext(to_string(stmt), to_string(currStmtNo));
							}
							prevIf = false;
						}
						else if (prevWhile) {
							pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
							prevWhile = false;
						}
						else {
							pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
						}
					}
					else {
						pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
					}
				}
				else {
					pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
					if (prevIf) {
						for (int stmt : prevIfStmtNo) {
							pkb.setNext(to_string(stmt), to_string(currStmtNo));
						}
						prevIf = false;
					}
					else if (prevWhile) {
						pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
						prevWhile = false;
					}
					else {
						pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
					}
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}

			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
		else if (line.find("else") != string::npos) {
			passedElse = true;
			elseStmtNo = currStmtNo;
			if (prevIf) {
				for (int stmt : prevIfStmtNo) {
					result.addPrevIfStmt(stmt);
				}
				prevIf = false;
			}
			else if (prevWhile) {
				result.addPrevIfStmt(prevWhileStmtNo);
				prevWhile = false;
			}
			else {
				result.addPrevIfStmt(currStmtNo - 1);
			}
			continue;
		}
		else {
			if (line.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(line, '}');
			}
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
	}
	if (prevIf) {
		for (int stmt : prevIfStmtNo) {
			result.addPrevIfStmt(stmt);
		}
		prevIf = false;
	}
	else if (prevWhile) {
		result.addPrevIfStmt(prevWhileStmtNo);
		prevWhile = false;
	}
	else {
		result.addPrevIfStmt(currStmtNo - 1);
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

	bool prevIf = false;
	bool prevWhile = false;
	vector<int> prevIfStmtNo;
	int prevWhileStmtNo = 0;

	string line;

	vector<string> toAdd = parseCondStmt(whileLine);
	for (string var : toAdd) {
		result.addUses(var);
		if (!isdigit(var.at(0))) {
			currProc.addUses(var);
			result.addCondExpr(var);
		}
	}
	while (getline(programFile, line)) {
		if (count(line, ';') > 1) {
			throw currStmtNo;
		}
		//Process to parse each line
		if (line.find("while") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(to_string(currStmtNo), "while");
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));
			nestingLevel++;
			NestedResult results = parseWhile(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			int stmt = results.getPrevWhileStmt();
			for (string var : modifies) {
				pkb.setVariable(var);
				pkb.setModifiesS(to_string(currStmtNo), var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(currStmtNo),var);
					result.addUses(var);
				}
				else {
					pkb.setVariable(var);
					pkb.setUsesS(to_string(currStmtNo), var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			vector<string> condExpr = results.getCondExpr();
			for (string var : condExpr) {
				pkb.setWhilePattern(to_string(currStmtNo), var);
			}
			if (currStmtNo != (startStmtNo + 1)) {
				pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(currStmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}

			prevWhile = true;
			prevWhileStmtNo = stmt;
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
		else if (line.find("if") != string::npos && line.find('{') != string::npos) {
			pkb.setStmt(to_string(currStmtNo), "if");
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));
			nestingLevel++;
			NestedResult results = parseIf(line, currStmtNo);
			vector<string> modifies = results.getModifies();
			vector<string> uses = results.getUses();
			vector<int> stmt = results.getPrevIfStmt();
			for (string var : modifies) {
				pkb.setVariable(var);
				pkb.setModifiesS(to_string(currStmtNo), var);
				result.addModifies(var);
				currProc.addModifies(var);
			}
			for (string var : uses) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(currStmtNo),var);
					result.addUses(var);
				}
				else {
					pkb.setVariable(var);
					pkb.setUsesS(to_string(currStmtNo), var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			vector<string> condExpr = results.getCondExpr();
			for (string var : condExpr) {
				pkb.setIfPattern(to_string(currStmtNo), var);
			}
			if (currStmtNo != (startStmtNo + 1)) {
				pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(currStmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}

			prevIf = true;
			prevIfStmtNo = stmt;
			prevStmtNo = currStmtNo;
			currStmtNo = results.lastStmtNo;
			if (nestingLevel < currNestingLevel) {
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
			pkb.setStmt(to_string(currStmtNo), "assign");
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));

			//Splits the assign statement by the = sign and get LHS and RHS
			int index = assign.find("=");
			string varMod = assign.substr(0, index);
			if (!(regex_match(varMod, name))) {
				throw stmtNo;
			}
			pkb.setVariable(varMod);
			pkb.setModifiesS(to_string(currStmtNo), varMod);
			result.addModifies(varMod);
			currProc.addModifies(varMod);

			string varUse = assign.substr(index + 1);

			//Calls to parse RHS of assign stmt
			vector<string> results = parseAssignRHS(varUse);
			string pattern = patternProcessor.infixtoRPNexpression(varUse);
			pkb.setAssignPattern(to_string(currStmtNo), pattern);

			for (string var : results) {
				if (isdigit(var.at(0))) {
					pkb.setConstant(to_string(currStmtNo),var);
					result.addUses(var);
				}
				else {
					pkb.setVariable(var);
					pkb.setUsesS(to_string(currStmtNo), var);
					result.addUses(var);
					currProc.addUses(var);
				}
			}

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(currStmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
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
			pkb.setStmt(to_string(currStmtNo), "read");
			pkb.setRead(readArg);
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));

			pkb.setModifiesS(to_string(currStmtNo), readArg);
			pkb.setVariable(readArg);
			result.addModifies(readArg);
			currProc.addModifies(readArg);

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(currStmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
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
			pkb.setStmt(to_string(currStmtNo), "print");
			pkb.setPrint(printArg);
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));

			pkb.setUsesS(to_string(currStmtNo), printArg);
			pkb.setVariable(printArg);
			result.addUses(printArg);
			currProc.addUses(printArg);

			if (currStmtNo != (startStmtNo + 1)) {
				pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(currStmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
		else if (line.find("call") != string::npos) {
			string callArg = line;
			if (callArg.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(line, '}');
				callArg.erase(std::remove(callArg.begin(), callArg.end(), '}'), callArg.end());
			}
			string proc = parseCall(callArg);
			pkb.setStmt(to_string(currStmtNo), "call");
			pkb.setCallStmt(to_string(currStmtNo), proc);
			pkb.setCallProc(currProc.getProcName(), proc);
			pkb.setParent(to_string(startStmtNo), to_string(currStmtNo));
			callStmts.push_back(make_pair(currStmtNo, proc));
			currProc.addCalls(proc);
			if (currStmtNo != (startStmtNo + 1)) {
				pkb.setFollows(to_string(prevStmtNo), to_string(currStmtNo));
				if (prevIf) {
					for (int stmt : prevIfStmtNo) {
						pkb.setNext(to_string(stmt), to_string(currStmtNo));
					}
					prevIf = false;
				}
				else if (prevWhile) {
					pkb.setNext(to_string(prevWhileStmtNo), to_string(currStmtNo));
					prevWhile = false;
				}
				else {
					pkb.setNext(to_string(prevStmtNo), to_string(currStmtNo));
				}
			}
			else {
				pkb.setNext(to_string(startStmtNo), to_string(currStmtNo));
			}
			prevStmtNo = currStmtNo;
			currStmtNo++;
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
		else {
			if (line.find("}") != string::npos) {
				nestingLevel = nestingLevel - count(line, '}');
			}
			if (nestingLevel < currNestingLevel) {
				break;
			}
		}
	}
	if (prevIf) {
		for (int stmt : prevIfStmtNo) {
			pkb.setNext(to_string(stmt), to_string(startStmtNo));
		}
		prevIf = false;
	}
	else if (prevWhile) {
		pkb.setNext(to_string(prevWhileStmtNo), to_string(startStmtNo));
		prevWhile = false;
	}
	else {
		pkb.setNext(to_string(prevStmtNo), to_string(startStmtNo));
	}

	result.setPrevWhileStmt(startStmtNo);
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
				var.erase(std::remove(var.begin(), var.end(), '!'), var.end());
			}
			if (!(regex_match(var, name) || regex_match(var, number))) {
				throw stmtNo;
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
							var.erase(std::remove(var.begin(), var.end(), '!'), var.end());
						}
						if (!(regex_match(var, name) || regex_match(var, number))) {
							throw stmtNo;
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
							var.erase(std::remove(var.begin(), var.end(), '!'), var.end());
						}
						if (!(regex_match(var, name) || regex_match(var, number))) {
							throw stmtNo;
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
					if (!(regex_match(var, name) || regex_match(var, number))) {
						throw stmtNo;
					}
					result.push_back(var);
				}
				break;
			}
		}
	}
	return result;
}

string Parser::removeOuterBrackets(string line) {
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

	vector<string> subresultFirst = parseCond(first);
	for (string element : subresultFirst) {
		if (element.find('!') != string::npos) {
			element.erase(std::remove(element.begin(), element.end(), '!'), element.end());
		}
		result.push_back(element);
	}

	vector<string> subresultSecond = parseCond(second);
	for (string element : subresultSecond) {
		if (element.find('!') != string::npos) {
			element.erase(std::remove(element.begin(), element.end(), '!'), element.end());
		}
		result.push_back(element);
	}
	return result;
}

vector<string> Parser::parseCond(string varUse) {
	string patternRHS = varUse;
	patternRHS.erase(std::remove(patternRHS.begin(), patternRHS.end(), ')'), patternRHS.end());
	patternRHS.erase(std::remove(patternRHS.begin(), patternRHS.end(), '('), patternRHS.end());
	string var = "";
	vector<string> result;
	int i = INT_MAX;
	while (patternRHS.size() > 0) {
		i = INT_MAX;
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
			if (var.find('!') != string::npos) {
				var.erase(std::remove(var.begin(), var.end(), '!'), var.end());
			}
			if (!(regex_match(var, name) || regex_match(var, number))) {
				throw stmtNo;
			}
			result.push_back(var);
			patternRHS = patternRHS.substr(i + 1);
		}
		else {
			var = patternRHS;
			if (var.find('!') != string::npos) {
				var.erase(std::remove(var.begin(), var.end(), '!'), var.end());
			}
			if (!(regex_match(var, name) || regex_match(var, number))) {
				throw stmtNo;
			}
			result.push_back(var);
			break;
		}
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
