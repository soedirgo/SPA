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

	//static bool insertAssignRelation(STMT_NO stmtNo, std::string varModified, VAR_LIST varUsed, CONST_LIST constUsed);

	static bool isConstUsedInAssign(STMT_NO stmtNo, std::string c);
	static bool isVarUsedInAssign(STMT_NO stmtNo, std::string c);

	//static bool setAssignStmt(STMT_NO stmtNo, std::string varModified);
	//static std::string getVarModifiedByAssignStmt(STMT_NO stmtNo);
	
	//static STMT_LIST getAssignStmtByVar(std::string varName);
	//static bool setAssignStmtByVar(STMT_NO stmtNo, std::string varName);

	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST(PROC p);


	//UPDATED APIS//

	//Variable Functions
	static bool setVar(VAR_NAME varName);
	static VAR_LIST getAllVar();

	//Stmt Functions
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);
	static STMT_LIST getAllStmt();
	static STMT_LIST getAllPrintStmt();
	static STMT_LIST getAllReadStmt();
	static STMT_LIST getAllAssignStmt();
	static STMT_LIST getAllWhileStmt();
	static STMT_LIST getAllIfStmt();
	static STMT_LIST getAllCallStmt();

	//Procedure Functions
	static PROC_LIST getAllProc();
	static bool setProc(PROC_NAME procName);

	//Print Functions
	static bool setPrintStmt(STMT_NO stmtNo, std::string varName);

	//Read Functions
	static bool setReadStmt(STMT_NO stmtNo, std::string varName);

	//Constant Functions
	static bool setConstant(CONST_VALUE constantVal, STMT_NO stmtNo);
	static CONST_LIST getAllConstant();

	//While Functions
	static bool setWhileUsesRelation(STMT_NO stmtNo, VAR_NAME varName);

	//If Functions
	static bool setIfUsesRelation(STMT_NO stmtNo, VAR_NAME varName);

	//Follow Functions
	static bool setFollowsRelation(STMT_NO followedBy, STMT_NO follow);
	static bool setFollowsStarRelation(STMT_NO followedBy, STMT_NO follow);
	static bool isFollowsRelationship(STMT_NO followedBy, STMT_NO follow);
	static bool isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follow);

	//Parent Functions
	static bool setParentRelation(STMT_NO parent, STMT_NO child);
	static bool setParentStarRelation(STMT_NO parent, STMT_NO child);
	static bool isParentRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentStarRelationship(STMT_NO parent, STMT_NO child);

	//Modifies Function
	static bool setModifiesStmtRelation(STMT_NO stmtNo, VAR_NAME varName);
	static bool setModifiesProcRelation(PROC_NAME procName, VAR_NAME varName);
	static bool isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	//Uses Function
	static bool setUsesStmtRelation(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesProcRelation(PROC_NAME procName, VAR_NAME varName);
	static bool isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	//Call Function
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME procName);
	static bool setCallProcRelation(PROC_NAME caller, PROC_NAME callee);
	static bool isCallRelationship(PROC_NAME caller, PROC_NAME callee);
	static bool isCallStarRelationship(PROC_NAME caller, PROC_NAME callee);

	//Next Function
	static bool setNextRelation(PROG_LINE n1, PROG_LINE n2);
	static bool isNextRelationship(PROG_LINE n1, PROG_LINE n2);
	static bool isNextStarRelationship(PROG_LINE n1, PROG_LINE n2);

private:
	static std::unordered_map<int, std::string> assignStmtTable;
	static std::unordered_map<std::string, std::unordered_set<int>> assignVarTable;
};
