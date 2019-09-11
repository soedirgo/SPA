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
	static bool setVar(std::string varName);
	static std::unordered_set<std::string> getAllVar();
	static bool isVarExist(std::string varName);
	// add a constant to constantTable
	static bool setConstant(std::string constantName);
	static std::unordered_set<std::string> getAllConstant();
	static bool isConstantExist(std::string constantName);
	// add a stmt to stmtTable
	static bool setStmt(int stmtNo, stmtType type);
	static std::unordered_set<int> getAllStmt();
	static bool isStmtExist(int stmtNo);
	//add var & stmt to varModifiesStmtTable
	static bool setModifiesStmtByVar(int stmtNo, std::string varName);
	static std::unordered_set<int> getModifiesStmtByVar(std::string varName);
	static std::unordered_set<std::string> getAllModifiesVar();
	//add var & stmt to varModifiesStmtTable
	static bool setUsesStmtByVar(int stmtNo, std::string varName);
	static std::unordered_set<int> getUsesStmtByVar(std::string varName);
	static std::unordered_set<std::string> getAllUsesVar();
	//add stmt & var to varModifiesByStmtTable
	static bool setModifiesVarByStmt(int stmtNo, std::string varName);
	static std::unordered_set<std::string> getModifiesVarByStmt(int stmtNo);
	static std::unordered_set<int> getAllModifiesStmt();
	//add stmt & var to varUsesByStmtTable
	static bool setUsesVarByStmt(int stmtNo, std::string varName);
	static std::unordered_set<std::string> getUsesVarByStmt(int stmtNo);
	static std::unordered_set<int> getAllUsesStmt();

	static bool isModifiesStmtVar(int stmtNo, std::string varName);
	static bool isUsesStmtVar(int stmtNo, std::string varName);

	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

private:
	static std::unordered_set<std::string> varTable;
	static std::unordered_set<std::string> constantTable;
	static std::unordered_map<int, stmtType> stmtTable;
	static std::unordered_map<std::string, std::unordered_set<int>> stmtModifiesByVarTable;
	static std::unordered_map<std::string, std::unordered_set<int>> stmtUsesByVarTable;
	static std::unordered_map<int, std::unordered_set<std::string>> varModifiesByStmtTable;
	static std::unordered_map<int, std::unordered_set<std::string>> varUsesByStmtTable;


};
