#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "AbstractType.h"

typedef short PROC;

class TNode;

//class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {

public:
	// Clear PKB database
	bool clear();
	/////////////////////////////////
	//Higher order wrapper functions
	/////////////////////////////////

	
	//Follow Functions
	static bool insertFollowRelation(STMT_NO followedBy, STMT_NO follow);
	static bool insertFollowStarRelation(STMT_NO followedBy, STMT_NO follow);
	static bool isFollowRelationship(STMT_NO followedBy, STMT_NO follow);
	static bool isFollowStarRelationship(STMT_NO followedBy, STMT_NO follow);
	static STMT_LIST getFollowedByStmtList(STMT_NO follow);
	static STMT_LIST getFollowStarStmtList(STMT_NO followedBy);
	static STMT_NO getFollowStmt(STMT_NO followedBy);
	
	//Parent Functions

	static bool insertParentRelation(STMT_NO parent, STMT_NO child);
	static bool insertParentStarRelation(STMT_NO parent, STMT_NO child);
	static bool isParentRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentStarRelationship(STMT_NO parent, STMT_NO child);
	static STMT_LIST getChildrenStmtList(STMT_NO parent);
	static STMT_LIST getParentStarStmtList(STMT_NO child);
	static STMT_NO getParentStmt(STMT_NO child);

	static bool insertModifiesRelation(STMT_NO stmtNo, std::string varName);
	static bool insertUsesRelation(STMT_NO stmtNo, std::string varName);
	static bool insertAssignRelation(STMT_NO stmtNo, std::string varModified, VAR_LIST varUsed, CONST_LIST constUsed);

	//static STMT_LIST getAllStmtByType(std::string stmtType);

	static bool isConstUsedInAssign(STMT_NO stmtNo, std::string c);
	static bool isVarUsedInAssign(STMT_NO stmtNo, std::string c);

	// add a variable to varTable
	static bool setVar(VAR_NAME varName);
	static VAR_LIST getAllVar();
	static bool isVarExist(std::string varName);
	// add a constant to constantTable
	static bool setConstant(std::string constantName, int stmtNo );
	static CONST_LIST getAllConstant();

	static bool isConstantExist(std::string constantName);
	static STMT_LIST getStmtByConst(std::string constantName);
	// add a stmt to stmtTable
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);
	static STMT_LIST getAllStmt();
	static bool isStmtExist(STMT_NO stmtNo);
	//add var & stmt to varModifiesStmtTable

	static STMT_LIST getModifiesStmtByVar(std::string varName);
	static VAR_LIST getAllModifiesVar();
	//add var & stmt to varModifiesStmtTable

	static STMT_LIST getUsesStmtByVar(std::string varName);
	static VAR_LIST getAllUsesVar();
	//add stmt & var to varModifiesByStmtTable
	static bool setModifiesVarByStmt(STMT_NO stmtNo, std::string varName);
	static VAR_LIST getModifiesVarByStmt(STMT_NO stmtNo);
	static STMT_LIST getAllModifiesStmt();
	//add stmt & var to varUsesByStmtTable
	static bool setUsesVarByStmt(STMT_NO stmtNo, std::string varName);
	static VAR_LIST getUsesVarByStmt(STMT_NO stmtNo);
	static STMT_LIST getAllUsesStmt();



	//add var & stmt to assign table 
	
	static bool setAssignStmt(STMT_NO stmtNo, std::string varModified);
	static std::string getVarModifiedByAssignStmt(STMT_NO stmtNo);
	
	static STMT_LIST getAssignStmtByVar(std::string varName);
	static bool setAssignStmtByVar(STMT_NO stmtNo, std::string varName);

	//Getters and setters for print table
	static bool setPrintStmt(STMT_NO stmtNo, std::string varName);
	static STMT_LIST getPrintStmtByVar(std::string varName);
	
	//Getters and setters for Read table
	static bool setReadStmt(STMT_NO stmtNo, std::string varName);
	static STMT_LIST getReadStmtByVar(std::string varName);

	STMT_LIST getCallStmtByVar(std::string procName);

	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST(PROC p);


	//UPDATED APIS
	static STMT_LIST getAllPrintStmt();
	static STMT_LIST getAllReadStmt();
	static STMT_LIST getAllAssignStmt();
	static STMT_LIST getAllWhileStmt();
	static STMT_LIST getAllIfStmt();
	static STMT_LIST getAllCallStmt();

	static std::unordered_set<std::string> getAllProc();
	bool setProc(std::string procName);

	static bool setModifiesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	static bool setUsesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	bool setCallStmt(STMT_NO stmtNo, PROC_NAME procName);
	bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	bool isCallRelationship(PROC_NAME caller, PROC_NAME callee);
	bool isCallStarRelationship(PROC_NAME caller, PROC_NAME callee);

	bool setNext(PROG_LINE n1, PROG_LINE n2);
	bool isNextRelationship(PROG_LINE n1, PROG_LINE n2);
	bool isNextStarRelationship(PROG_LINE n1, PROG_LINE n2);

private:
	static std::unordered_set<std::string> varTable;
	static std::unordered_map<std::string, std::unordered_set<int>>constantTable;
	static std::unordered_map<std::string, std::unordered_set<int>> stmtModifiesByVarTable;
	static std::unordered_map<std::string, std::unordered_set<int>> stmtUsesByVarTable;
	static std::unordered_map<int, std::string> assignStmtTable;
	static std::unordered_map<std::string, std::unordered_set<int>> assignVarTable;
	static std::unordered_map<std::string, std::unordered_set<int>> printTable;
	static std::unordered_map<std::string, std::unordered_set<int>> readTable;
	static std::unordered_map<std::string, std::unordered_set<int>> callTable;
};
