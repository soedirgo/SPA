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

	// Clear PKB database
	static bool clear();

	//Variable Functions
	static bool setVar(VAR_NAME varName);
	static VAR_LIST getVariable();

	//Stmt Functions
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);
	static STMT_LIST getStmt();
	static STMT_LIST getPrint();
	static STMT_LIST getRead();
	static STMT_LIST getAssign();
	static STMT_LIST getWhile();
	static STMT_LIST getIf();
	static STMT_LIST getCall();
	static STMT_LIST getProgLine();

	//Procedure Functions
	static PROC_LIST getProcedures();
	static bool setProcedure(PROC_NAME procName);

	//Print Functions
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);

	//Read Functions
	static bool setRead(STMT_NO stmtNo, VAR_NAME varName);

	//Constant Functions
	static bool setConstant(STMT_NO stmtNo, CONST_VAL constantVal);
	static CONST_LIST getConstants();
	//static CONST_VAL getConstantValByStmt(STMT_NO stmtNo); 

	//While Functions
	static bool setWhileCondition(STMT_NO stmtNo, VAR_NAME varName);

	//If Functions
	static bool setIfCondition(STMT_NO stmtNo, VAR_NAME varName);

	//Follow Functions
	static bool setFollows(STMT_NO followedBy, STMT_NO follow);
	static bool setFollowsT(STMT_NO followedBy, STMT_NO follow);
	static bool isFollowsRelationship(STMT_NO followedBy, STMT_NO follow);
	static bool isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follow);

	static TABLE getAllFollowedByFollowsStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllFollowedByStmt(STMT_TYPE type, STMT_NO follows);
	static STMT_LIST getAllFollowsStmt(STMT_NO followedBy, STMT_TYPE type1);
	static TABLE getAllFollowedByFollowsStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllFollowedByStarStmt(STMT_TYPE type, STMT_NO follows);
	static STMT_LIST getAllFollowsStarStmt(STMT_NO followedBy, STMT_TYPE type);

	static bool isFollows(STMT_REF s1, STMT_REF s2);
	static TABLE getFollows(STMT_REF s1, STMT_REF s2);

	//Parent Functions
	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentT(STMT_NO parent, STMT_NO child);
	static bool isParentRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentStarRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentExist(STMT_NO child);
	static STMT_NO getParentStmt(STMT_NO child);

	static TABLE getAllParentChildStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllParentStmt(STMT_TYPE type1, STMT_NO follows);
	static STMT_LIST getAllChildStmt(STMT_NO followedBy, STMT_TYPE type1);
	static TABLE getAllParentChildStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllParentStarStmt(STMT_TYPE type1, STMT_NO follows);
	static STMT_LIST getAllChildStarStmt(STMT_NO followedBy, STMT_TYPE type1);

	static bool isParent(STMT_REF s1, STMT_REF s2);
	static TABLE getParent(STMT_REF s1, STMT_REF s2);

	//Modifies Function
	static bool setModifiesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool setModifiesProc(PROC_NAME procName, VAR_NAME varName);
	static bool isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);
	static bool isModifiesProcRelationship(PROC_NAME procName, VAR_NAME varName);

	static bool isModifiesS(STMT_REF s1, ENT_REF e2);
	static bool isModifiesP(ENT_REF e1, ENT_REF e2);

	//Uses Function
	static bool setUsesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesProc(PROC_NAME procName, VAR_NAME varName);
	static bool isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesProcRelationship(PROC_NAME procName, VAR_NAME varName);

	static bool isUsesS(STMT_REF s1, ENT_REF e2);
	static bool isUsesP(ENT_REF e1, ENT_REF e2);

	//Call Function
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME procName);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallT(PROC_NAME caller, PROC_NAME callee);
	static bool isCallRelationship(PROC_NAME caller, PROC_NAME callee);
	static bool isCallStarRelationship(PROC_NAME caller, PROC_NAME callee);

	static TABLE getAllCallerCalleeProc();
	static PROC_LIST getAllCallerProc(PROC_NAME procName);
	static PROC_LIST getAllCalleProc(PROC_NAME procName);
	static TABLE getAllCallerCalleeStarProc();
	static PROC_LIST getAllCallerStarProc(PROC_NAME procName);
	static PROC_LIST getAllCalleStarProc(PROC_NAME procName);

	static bool isCalls(PROC_NAME p1, PROC_NAME p2);
	static TABLE getCall(PROC_NAME p1, PROC_NAME p2);

	//Next Function
	static bool setNext(PROG_LINE n1, PROG_LINE n2);
	static bool isNextRelationship(PROG_LINE n1, PROG_LINE n2);
	static bool isNextStarRelationship(PROG_LINE n1, PROG_LINE n2);

	static TABLE getAllNextByLineNextLineStmt();
	static LINE_LIST getAllNextByLineStmt(PROG_LINE progLine);
	static LINE_LIST getAllNextLineStmt(PROG_LINE progLine);
	static TABLE getAllNextByLineNextLineStarStmt();
	static LINE_LIST getAllNextByLineStarStmt(PROG_LINE progLine);
	static LINE_LIST getAllNextLineStarStmt(PROG_LINE progLine);

	static bool isNext(STMT_REF s1, STMT_REF s2);
	static TABLE getNext(STMT_REF s1, STMT_REF s2);
private:
	static std::unordered_map<int, std::string> assignStmtTable;
	static std::unordered_map<std::string, std::unordered_set<int>> assignVarTable;
};
