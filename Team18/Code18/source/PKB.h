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
	static bool setVariable(VAR_NAME varName);
	static VAR_LIST getVariables();

	//Stmt Functions
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);
	static STMT_LIST getStmts();
	static STMT_LIST getPrints();
	static STMT_LIST getReads();
	static STMT_LIST getAssigns();
	static STMT_LIST getWhiles();
	static STMT_LIST getIfs();
	static STMT_LIST getCalls();
	static STMT_LIST getProgLines();

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

	//Follow Bool Evaluation
	static bool isFollowsAnyAny();
	static bool isFollowsAnyIdent(STMT_NO s2);
	static bool isFollowsIdentAny(STMT_NO s1);
	static bool isFollowsIdentIdent(STMT_NO s1, STMT_NO s2);

	static bool isFollowsTAnyAny();
	static bool isFollowsTAnyIdent(STMT_NO s2);
	static bool isFollowsTIdentAny(STMT_NO s1);
	static bool isFollowsTIdentIdent(STMT_NO s1, STMT_NO s2);

	//Follow Table Evaluation
	static TABLE getFollowsAnyEnt(STMT_TYPE s2);
	static TABLE getFollowsIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getFollowsEntAny(STMT_TYPE s1);
	static TABLE getFollowsEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static TABLE getFollowsTAnyEnt(STMT_TYPE s2);
	static TABLE getFollowsTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getFollowsTEntAny(STMT_TYPE s1);
	static TABLE getFollowsTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsTEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	//Parent Functions
	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentT(STMT_NO parent, STMT_NO child);
	static bool isParentExist(STMT_NO child);
	static STMT_NO getParentStmt(STMT_NO child);

	//Parent Bool Evaluation 
	static bool isParentAnyAny();
	static bool isParentAnyIdent(STMT_NO s2);
	static bool isParentIdentAny(STMT_NO s1);
	static bool isParentIdentIdent(STMT_NO s1, STMT_NO s2);

	static bool isParentTAnyAny();
	static bool isParentTAnyIdent(STMT_NO s2);
	static bool isParentTIdentAny(STMT_NO s1);
	static bool isParentTIdentIdent(STMT_NO s1, STMT_NO s2);
	
	//Parent Table Evaluation
	static TABLE getParentAnyEnt(STMT_TYPE s2);
	static TABLE getParentIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getParentEntAny(STMT_TYPE s1);
	static TABLE getParentEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static TABLE getParentTAnyEnt(STMT_TYPE s2);
	static TABLE getParentTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getParentTEntAny(STMT_TYPE s1);
	static TABLE getParentTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentTEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	//Modifies Function
	static bool setModifiesS(STMT_NO stmtNo, VAR_NAME varName);
	static bool setModifiesP(PROC_NAME procName, VAR_NAME varName);

	//Modifies Bool Evaluation
	static bool isModifiesSIdentAny(STMT_NO stmtNo);
	static bool isModifiesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName);

	static bool isModifiesPIdentAny(PROC_NAME procName);
	static bool isModifiesPIdentIdent(PROC_NAME procName, VAR_NAME varName);

	//Modifies Table Evaluation
	static STMT_LIST getModifiesSEntAny(STMT_TYPE type);
	static TABLE getModifiesSEntIdent(STMT_TYPE type, VAR_NAME varName);
	static VAR_LIST getModifiesSIdentEnt(STMT_NO stmtNo);
	static TABLE getModifiesSEntEnt(STMT_TYPE type);

	static PROC_LIST getModifiesPEntAny();
	static PROC_LIST getModifiesPEntIdent(VAR_NAME varName);
	static VAR_LIST getModifiesPIdentEnt(PROC_NAME procName);
	static TABLE getModifiesPEntEnt();

	//Uses Function
	static bool setUsesS(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesP(PROC_NAME procName, VAR_NAME varName);

	//Uses Bool Evaluation
	static bool isUsesSIdentAny(STMT_NO stmtNo);
	static bool isUsesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName);

	static bool isUsesPIdentAny(PROC_NAME procName);
	static bool isUsesPIdentIdent(PROC_NAME procName, VAR_NAME varName);

	//Uses Table Evaluation
	static STMT_LIST getUsesSEntAny(STMT_TYPE type);
	static STMT_LIST getUsesSEntIdent(STMT_TYPE type, VAR_NAME varName);
	static VAR_LIST getUsesSIdentEnt(STMT_NO stmtNo);
	static TABLE getUsesSEntEnt(STMT_TYPE type);

	static PROC_LIST getUsesPEntAny();
	static PROC_LIST getUsesPEntIdent(VAR_NAME varName);
	static VAR_LIST getUsesPIdentEnt(PROC_NAME procName);
	static TABLE getUsesPEntEnt();

	//Call Function
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME procName);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallT(PROC_NAME caller, PROC_NAME callee);

	//Call Bool Evaluation
	static bool isCallsAnyAny();
	static bool isCallsAnyIdent(PROC_NAME p2);
	static bool isCallsIdentAny(PROC_NAME p1);
	static bool isCallsIdentIdent(PROC_NAME p1, PROC_NAME p2);

	static bool isCallsTAnyAny();
	static bool isCallsTAnyIdent(PROC_NAME p2);
	static bool isCallsTIdentAny(PROC_NAME p1);
	static bool isCallsTIdentIdent(PROC_NAME p1, PROC_NAME p2);

	//Call Table Evaluation
	static TABLE getCallsAnyEnt();
	static TABLE getCallsIdentEnt(PROC_NAME p1);
	static TABLE getCallsEntAny();
	static TABLE getCallsEntIdent(PROC_NAME p2);
	static TABLE getCallsEntEnt();

	static TABLE getCallsTAnyEnt();
	static TABLE getCallsTIdentEnt(PROC_NAME p1);
	static TABLE getCallsTEntAny();
	static TABLE getCallsTEntIdent(PROC_NAME p2);
	static TABLE getCallsTEntEnt();

	//Next Function
	static bool setNext(PROG_LINE n1, PROG_LINE n2);

	//Next Bool Evaluation
	static bool isNextAnyAny();
	static bool isNextAnyIdent(PROG_LINE n2);
	static bool isNextIdentAny(PROG_LINE n1);
	static bool isNextIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static bool isNextTAnyAny();
	static bool isNextTAnyIdent(PROG_LINE n2);
	static bool isNextTIdentAny(PROG_LINE n1);
	static bool isNextTIdentIdent(PROG_LINE n1, PROG_LINE n2);

	//Next Table Evaluation
	static TABLE getNextAnyEnt();
	static TABLE getNextIdentEnt(PROG_LINE n1);
	static TABLE getNextEntAny();
	static TABLE getNextEntIdent(PROG_LINE n2);
	static TABLE getNextEntEnt();

	static TABLE getNextTAnyEnt();
	static TABLE getNextTIdentEnt(PROG_LINE n1);
	static TABLE getNextTEntAny();
	static TABLE getNextTEntIdent(PROG_LINE n2);
	static TABLE getNextTEntEnt();

private:
	static std::unordered_map<int, std::string> assignStmtTable;
	static std::unordered_map<std::string, std::unordered_set<int>> assignVarTable;
};
