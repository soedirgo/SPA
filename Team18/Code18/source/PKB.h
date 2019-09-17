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

	//add var & stmt to assign table 
	static std::unordered_set<int> getAllAssignStmt();
	static bool setAssignStmt(int stmtNo, std::string varModified);
	static std::string getVarModifiedByAssignStmt(int stmtNo);
	
	static std::unordered_set<int> getAssignStmtByVar(std::string varName);
	static bool setAssignStmtByVar(int stmtNo, std::string varName);


	//Getters and setters for while table 
	static std::unordered_set<int> getAllWhileStmt();
	static bool setWhileStmt(int stmtNo);

	//Getters and setters for if table
	static std::unordered_set<int> getAllIfStmt();
	static bool setIfStmt(int stmtNo);

	//Getters and setters for print table
	static std::unordered_set<int> getAllPrintStmt();
	static bool setPrintStmt(int stmtNo, std::string varName);
	static std::unordered_set<int> getPrintStmtByVar(std::string varName);
	
	//Getters and setters for Read table
	static std::unordered_set<int> getAllReadStmt();
	static bool setReadStmt(int stmtNo, std::string varName);
	static std::unordered_set<int> getReadStmtByVar(std::string varName);

	//Getters and setters for Procedure table
	static std::unordered_set<std::string> getAllProc();
	bool setProc(std::string procName);


	//Getters and setters for Call table
	static std::unordered_set<int> getAllCallStmt();
	bool setCallStmt(int stmtNo, std::string procName);
	std::unordered_set<int> getCallStmtByVar(std::string procName);


	//Methods(varName) for modifies and uses SubTables
	//static unordered_set<int> getStmtsThatModVarByAssign(string varName);
	


	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST(PROC p);

private:
	static std::unordered_set<std::string> varTable;
	static std::unordered_set<std::string> constantTable;
	static std::unordered_map<int, stmtType> stmtTable;

	static std::unordered_map<std::string, std::unordered_set<int>> stmtModifiesByVarTable;
	static std::unordered_map<std::string, std::unordered_set<int>> stmtUsesByVarTable;
	static std::unordered_map<int, std::unordered_set<std::string>> varModifiesByStmtTable;
	static std::unordered_map<int, std::unordered_set<std::string>> varUsesByStmtTable;

	static std::unordered_map<int, std::string> assignStmtTable;
	static std::unordered_map<std::string, std::unordered_set<int>> assignVarTable;

	static std::unordered_set<int> whileTable;
	static std::unordered_set<int> ifTable;
	static std::unordered_map<std::string, std::unordered_set<int>> printTable;
	static std::unordered_map<std::string, std::unordered_set<int>> readTable;
	static std::unordered_set<std::string> procedureTable;
	static std::unordered_map<std::string, std::unordered_set<int>> callTable;

	/*
	
	
	static unordered_set<int> callTable; //Not for iteration 1 
	
	*/
	
};
