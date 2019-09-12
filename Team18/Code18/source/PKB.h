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
	static bool setUsesVarByStmt(int stmtNo, string varName);
	static unordered_set<string> getUsesVarByStmt(int stmtNo);
	static unordered_set<int> getAllUsesStmt();

	static bool isModifiesStmtVar(int stmtNo, std::string varName);
	static bool isUsesStmtVar(int stmtNo, std::string varName);

	//add var & stmt to assign table 
	static unordered_set<int> getAllAssignStmt();
	static bool setAssignStmt(int stmtNo, string varModified); 
	static string getVarModifiedByAssignStmt(int stmtNo);
	
	static unordered_set<int> getAssignStmtByVar(string varName);
	static bool setAssignStmtByVar(int stmtNo, string varName);


	//Getters and setters for while table 
	static unordered_set<int> getAllWhileStmt(); 
	static bool setWhileStmt(int stmtNo);

	//Getters and setters for if table
	static unordered_set<int> getAllIfStmt();
	static bool setIfStmt(int stmtNo);

	//Getters and setters for print table
	static unordered_set<int> getAllPrintStmt(); 
	static bool setPrintStmt(int stmtNo, string varName);
	static unordered_set<int> getPrintStmtByVar(string varName);
	
	//Getters and setters for Read table
	static unordered_set<int> getAllReadStmt();
	static bool setReadStmt(int stmtNo, string varName);
	static unordered_set<int> getReadStmtByVar(string varName);

	//Getters and setters for Procedure table
	static unordered_set<string> getAllProc();
	bool setProc(string procName);


	//Getters and setters for Call table
	static unordered_set<int> getAllCallStmt();
	bool setCallStmt(int stmtNo, string procName);
	unordered_set<int> getCallStmtByVar(string procName);


	//Methods(varName) for modifies and uses SubTables
	//static unordered_set<int> getStmtsThatModVarByAssign(string varName);
	


	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST(PROC p);

private:
	static unordered_set<string> varTable;
	static unordered_set<string> constantTable;
	static unordered_map<int, stmtType> stmtTable;

	static unordered_map<string, unordered_set<int>> stmtModifiesByVarTable;
	static unordered_map<string, unordered_set<int>> stmtUsesByVarTable;
	static unordered_map<int, unordered_set<string>> varModifiesByStmtTable;
	static unordered_map<int, unordered_set<string>> varUsesByStmtTable;

	static unordered_map<int, string> assignStmtTable;
	static unordered_map<string, unordered_set<int>> assignVarTable;

	static unordered_set<int> whileTable;
	static unordered_set<int> ifTable;
	static unordered_map<string, unordered_set<int>> printTable;
	static unordered_map<string, unordered_set<int>> readTable;
	static unordered_set<string> procedureTable; 
	static unordered_map<string, unordered_set<int>> callTable;

	/*
	
	
	static unordered_set<int> callTable; //Not for iteration 1 
	
	*/
	
};
