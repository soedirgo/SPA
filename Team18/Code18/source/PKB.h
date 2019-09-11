#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

typedef short PROC;

class TNode;

//class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

enum stmtType { Read, Print, Assign, While, If, Call };

class PKB {

	
	
public:
	// Clear PKB database
	bool clear();
	// add a variable to varTable
	static bool setVar(string varName);
	static unordered_set<string> getAllVar();
	static bool isVarExist(string varName);
	// add a constant to constantTable
	static bool setConstant(string constantName);
	static unordered_set<string> getAllConstant();
	static bool isConstantExist(string constantName);
	// add a stmt to stmtTable
	static bool setStmt(int stmtNo, stmtType type);
	static unordered_set<int> getAllStmt();
	static bool isStmtExist(int stmtNo);
	//add var & stmt to varModifiesStmtTable
	static bool setModifiesStmtByVar(int stmtNo, string varName);
	static unordered_set<int> getModifiesStmtByVar(string varName);
	static  unordered_set<string> getAllModifiesVar();
	//add var & stmt to varModifiesStmtTable
	static bool setUsesStmtByVar(int stmtNo, string varName);
	static unordered_set<int> getUsesStmtByVar(string varName);
	static  unordered_set<string> getAllUsesVar();
	//add stmt & var to varModifiesByStmtTable
	static bool setModifiesVarByStmt(int stmtNo, string varName);
	static unordered_set<string> getModifiesVarByStmt(int stmtNo);
	static  unordered_set<int> getAllModifiesStmt();
	//add stmt & var to varUsesByStmtTable
	static bool setUsesVarByStmt(int stmtNo, string varName);
	static unordered_set<string> getUsesVarByStmt(int stmtNo);
	static  unordered_set<int> getAllUsesStmt();

	static bool isModifiesStmtVar(int stmtNo, string varName);
	static bool isUsesStmtVar(int stmtNo, string varName);

	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

private:
	static unordered_set<string> varTable;
	static unordered_set<string> constantTable;
	static unordered_map<int, stmtType> stmtTable;
	static unordered_map<string, unordered_set<int>> stmtModifiesByVarTable;
	static unordered_map<string, unordered_set<int>> stmtUsesByVarTable;
	static unordered_map<int, unordered_set<string>> varModifiesByStmtTable;
	static unordered_map<int, unordered_set<string>> varUsesByStmtTable;


};
