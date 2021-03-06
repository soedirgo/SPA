#include <string>
#include <vector>
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollows.h"
#include "PKBUses.h"
#include "PKBModifies.h"
#include "PKBStmt.h"
#include "PKBProcedure.h"
#include "PKBVariable.h"
#include "PKBCall.h"
#include "PKBNext.h"
#include "PKBPrint.h"
#include "PKBRead.h"
#include "PKBConstant.h"
#include "PKBPattern.h"
#include "PKBAffects.h"
#include "PKBWith.h"
using namespace std;

void PKB::clear()
{
	PKBCall::clear();
	PKBConstant::clear();
	PKBFollows::clear();
	PKBModifies::clear();
	PKBNext::clear();
	PKBParent::clear();
	PKBPattern::clear();
	PKBPrint::clear();
	PKBProcedure::clear();
	PKBRead::clear();
	PKBStmt::clear();
	PKBUses::clear();
	PKBVariable::clear();
}

void PKB::clearTempPKB()
{
	//Clear Next* table
	//Clear Affects and Affects* Table
	PKBNext::clearCache();
	PKBAffects::clearCache();
}

//////////////////////////////////
//Variable Functions
//////////////////////////////////

//Set variable into PKB
void PKB::setVariable(VAR_NAME varName) {
	 PKBVariable::setVariable(varName);
}
//Get all variables from PKB
LIST_OF_VAR_NAME PKB::getVariables() {
	return PKBVariable::getVariables();
}

//////////////////////////////////
//Stmt Functions
//////////////////////////////////

//Set StmtNo into PKB with its type
void PKB::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	 PKBStmt::setStmt(stmtNo, type);
}
//Set all StmtNo from PKB
STMT_LIST PKB::getStmts() {
	return PKBStmt::getStmts();
}
//Set all while StmtNo from PKB
STMT_LIST PKB::getWhiles() {
	return PKBStmt::getStmtsByType("while");
};
//Set all assign StmtNo from PKB
STMT_LIST PKB::getAssigns() {
	return PKBStmt::getStmtsByType("assign");
}
//Set all ifs StmtNo from PKB
STMT_LIST PKB::getIfs() {
	return PKBStmt::getStmtsByType("if");
};
//Set all print StmtNo from PKB
STMT_LIST PKB::getPrints() {
	return PKBStmt::getStmtsByType("print");
};
//Set all read StmtNo from PKB
STMT_LIST PKB::getReads() {
	return PKBStmt::getStmtsByType("read");
};
//Set all call StmtNo from PKB
STMT_LIST PKB::getCalls() {
	return PKBStmt::getStmtsByType("call");
};
//Set all prog_line StmtNo from PKB
STMT_LIST PKB::getProgLines() {
	return PKBStmt::getStmts();
}
//Get stmtType by stmtNo from PKB
STMT_TYPE PKB::getTypeByStmtNo(STMT_NO stmtNo) {
	return PKBStmt::getTypeByStmtNo(stmtNo);
}

//Get stmtNo by stmtType from PKB
STMT_LIST PKB::getStmtsByType(STMT_TYPE type) {
	return PKBStmt::getStmtsByType(type);
}

////////////////////////////////////
// ProecedureTable APIs
////////////////////////////////////

void PKB::setProcByStmt(STMT_NO stmtNo, PROC_NAME proc) {
	 PKBProcedure::setProcByStmt(stmtNo, proc);
};

void PKB::setProcedure(PROC_NAME procName, STMT_NO start, STMT_LIST end) {
	 PKBProcedure::setProcedure(procName, start, end);
};

PROC_NAME PKB::getProcByStmt(STMT_NO stmtNo) {
	return PKBProcedure::getProcByStmt(stmtNo);
}

LIST_OF_PROC_NAME PKB::getProcedures() {
	return PKBProcedure::getProcedures();
};

STMT_LIST PKB::getProcedureStartEnd(PROC_NAME procName) {
	return PKBProcedure::getProcedureStartEnd(procName);
}

////////////////////////////////////
// printTable APIs
////////////////////////////////////
void PKB::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	 PKBPrint::setPrint(stmtNo, varName);
};

LIST_OF_VAR_NAME PKB::getAllPrintVar() {
	return PKBPrint::getAllPrintVar();
}

////////////////////////////////////
// ReadTable APIs
////////////////////////////////////
void PKB::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	PKBRead::setRead(stmtNo, varName);
};

LIST_OF_VAR_NAME PKB::getAllReadVar() {
	return PKBRead::getAllReadVar();
}

////////////////////////////////////
// constantTable APIs
////////////////////////////////////
void PKB::setConstant(CONST_VAL constantVal) {
	 PKBConstant::setConstant(constantVal);
}

LIST_OF_CONS_VAL PKB::getConstants() {
	return PKBConstant::getConstants();
}

////////////////////////////////////
//Follows 
////////////////////////////////////
void PKB::setFollows(STMT_NO followedBy, STMT_NO follow) {
	 PKBFollows::setFollows(followedBy, follow);
}

void PKB::setFollowsT(STMT_NO followedBy, STMT_NO follow) {
	 PKBFollows::setFollowsT(followedBy, follow);
}

STMT_NO PKB::getFollowsStmt(STMT_NO followedBy) {
	return PKBFollows::getFollowsStmt(followedBy);
}

//Follow Bool Evaluation
bool PKB::isFollowsAnyAny() {
	return PKBFollows::isFollowsAnyAny();
}
bool PKB::isFollowsAnyIdent(STMT_NO s2) {
	return PKBFollows::isFollowsAnyIdent(s2);
}
bool PKB::isFollowsIdentAny(STMT_NO s1) {
	return PKBFollows::isFollowsIdentAny(s1);
}
bool PKB::isFollowsIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBFollows::isFollowsIdentIdent(s1, s2);
}

bool PKB::isFollowsTAnyAny() {
	return PKBFollows::isFollowsTAnyAny();
}
bool PKB::isFollowsTAnyIdent(STMT_NO s2) {
	return PKBFollows::isFollowsTAnyIdent(s2);
}
bool PKB::isFollowsTIdentAny(STMT_NO s1) {
	return PKBFollows::isFollowsTIdentAny(s1);
}
bool PKB::isFollowsTIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBFollows::isFollowsTIdentIdent(s1, s2);
}

//Follow Table Evaluation
TABLE PKB::getFollowsAnyEnt(STMT_TYPE s2) {
	return PKBFollows::getFollowsAnyEnt(s2);
}
TABLE PKB::getFollowsIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsIdentEnt(s1, s2);
}
TABLE PKB::getFollowsEntAny(STMT_TYPE s1) {
	return PKBFollows::getFollowsEntAny(s1);
}
TABLE PKB::getFollowsEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBFollows::getFollowsEntIdent(s1, s2);
}
TABLE PKB::getFollowsEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsEntEnt(s1, s2);
}

TABLE PKB::getFollowsTAnyEnt(STMT_TYPE s2) {
	return PKBFollows::getFollowsTAnyEnt(s2);
}
TABLE PKB::getFollowsTIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsTIdentEnt(s1, s2);
}
TABLE PKB::getFollowsTEntAny(STMT_TYPE s1) {
	return PKBFollows::getFollowsTEntAny(s1);
}
TABLE PKB::getFollowsTEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBFollows::getFollowsTEntIdent(s1, s2);
}
TABLE PKB::getFollowsTEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsTEntEnt(s1, s2);
}
////////////////////////////////////
//Parents
////////////////////////////////////
void PKB::setParent(STMT_NO parent, STMT_NO child) {
	 PKBParent::setParent(parent, child);
}

void PKB::setParentT(STMT_NO parent, STMT_NO child) {
	 PKBParent::setParentT(parent, child);
}

//Parent Evaluation Bool Functions
bool PKB::isParentAnyAny() { 
	return PKBParent::isParentAnyAny();
}
bool PKB::isParentAnyIdent(STMT_NO s2) {
	return PKBParent::isParentAnyIdent(s2);
}
bool PKB::isParentIdentAny(STMT_NO s1) {
	return PKBParent::isParentIdentAny(s1);
}
bool PKB::isParentIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBParent::isParentIdentIdent(s1, s2);
}

bool PKB::isParentTAnyAny() {
	return PKBParent::isParentTAnyAny();
}
bool PKB::isParentTAnyIdent(STMT_NO s2) {
	return PKBParent::isParentTAnyIdent(s2);
}
bool PKB::isParentTIdentAny(STMT_NO s1) {
	return PKBParent::isParentTIdentAny(s1);
}
bool PKB::isParentTIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBParent::isParentTIdentIdent(s1, s2);
}

//Parent Evaluation Table Functions
TABLE PKB::getParentAnyEnt(STMT_TYPE s2) {
	return PKBParent::getParentAnyEnt(s2);
}
TABLE PKB::getParentIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBParent::getParentIdentEnt(s1,s2);
}
TABLE PKB::getParentEntAny(STMT_TYPE s1) {
	return PKBParent::getParentEntAny(s1);
}
TABLE PKB::getParentEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBParent::getParentEntIdent(s1, s2);
}
TABLE PKB::getParentEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBParent::getParentEntEnt(s1, s2);
}

TABLE PKB::getParentTAnyEnt(STMT_TYPE s2) {
	return PKBParent::getParentTAnyEnt(s2);
}
TABLE PKB::getParentTIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBParent::getParentTIdentEnt(s1, s2);
}
TABLE PKB::getParentTEntAny(STMT_TYPE s1) {
	return PKBParent::getParentTEntAny(s1);
}
TABLE PKB::getParentTEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBParent::getParentTEntIdent(s1,s2);
}
TABLE PKB::getParentTEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBParent::getParentTEntEnt(s1, s2);
}

////////////////////////////////////
//Modifies
////////////////////////////////////
void PKB::setModifiesS(STMT_NO stmtNo, VAR_NAME varName) {
	 PKBModifies::setModifiesS(stmtNo, varName);
};

void PKB::setModifiesP(PROC_NAME procName, VAR_NAME varName) {
	 PKBModifies::setModifiesP(procName, varName);
};

//Modifies Bool Evaluation
bool PKB::isModifiesSIdentAny(STMT_NO stmtNo) {
	return PKBModifies::isModifiesSIdentAny(stmtNo);
}
bool PKB::isModifiesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBModifies::isModifiesSIdentIdent(stmtNo, varName);
}

bool PKB::isModifiesPIdentAny(PROC_NAME procName) {
	return PKBModifies::isModifiesPIdentAny(procName);
}
bool PKB::isModifiesPIdentIdent(PROC_NAME procName, VAR_NAME varName) {
	return PKBModifies::isModifiesPIdentIdent(procName, varName);
}

//Modifies Table Evaluation
STMT_LIST PKB::getModifiesSEntAny(STMT_TYPE type) {
	return PKBModifies::getModifiesSEntAny(type);
}
TABLE PKB::getModifiesSEntIdent(STMT_TYPE type, VAR_NAME varName) {
	return PKBModifies::getModifiesSEntIdent(type, varName);
}
LIST_OF_VAR_NAME PKB::getModifiesSIdentEnt(STMT_NO stmtNo) {
	return PKBModifies::getModifiesSIdentEnt(stmtNo);
}
TABLE PKB::getModifiesSEntEnt(STMT_TYPE type) {
	return PKBModifies::getModifiesSEntEnt(type);
}

LIST_OF_PROC_NAME PKB::getModifiesPEntAny() {
	return PKBModifies::getModifiesPEntAny();
}
LIST_OF_PROC_NAME PKB::getModifiesPEntIdent(VAR_NAME varName) {
	return PKBModifies::getModifiesPEntIdent(varName);
}
LIST_OF_VAR_NAME PKB::getModifiesPIdentEnt(PROC_NAME procName) {
	return PKBModifies::getModifiesPIdentEnt(procName);
}
TABLE PKB::getModifiesPEntEnt() {
	return PKBModifies::getModifiesPEntEnt();
}

////////////////////////////////////
//Uses
////////////////////////////////////
void PKB::setUsesS(STMT_NO stmtNo, VAR_NAME varName) {
	 PKBUses::setUsesS(stmtNo, varName);

};

void PKB::setUsesP(PROC_NAME procName, VAR_NAME varName) {
	 PKBUses::setUsesP(procName, varName);
};

//Uses Bool Evaluation
bool PKB::isUsesSIdentAny(STMT_NO stmtNo) {
	return PKBUses::isUsesSIdentAny(stmtNo);
}
bool PKB::isUsesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBUses::isUsesSIdentIdent(stmtNo, varName);
}

bool PKB::isUsesPIdentAny(PROC_NAME procName) {
	return PKBUses::isUsesPIdentAny(procName);
}
bool PKB::isUsesPIdentIdent(PROC_NAME procName, VAR_NAME varName) {
	return PKBUses::isUsesPIdentIdent(procName, varName);
}

//Uses Table Evaluation
STMT_LIST PKB::getUsesSEntAny(STMT_TYPE type) {
	return PKBUses::getUsesSEntAny(type);
}
STMT_LIST PKB::getUsesSEntIdent(STMT_TYPE type, VAR_NAME varName) {
	return  PKBUses::getUsesSEntIdent(type, varName);
}
LIST_OF_VAR_NAME PKB::getUsesSIdentEnt(STMT_NO stmtNo) {
	return  PKBUses::getUsesSIdentEnt(stmtNo);
}
TABLE PKB::getUsesSEntEnt(STMT_TYPE type) {
	return PKBUses::getUsesSEntEnt(type);
}

LIST_OF_PROC_NAME PKB::getUsesPEntAny() {
	return PKBUses::getUsesPEntAny();
}
LIST_OF_PROC_NAME PKB::getUsesPEntIdent(VAR_NAME varName) {
	return PKBUses::getUsesPEntIdent(varName);
}
LIST_OF_VAR_NAME PKB::getUsesPIdentEnt(PROC_NAME procName) {
	return PKBUses::getUsesPIdentEnt(procName);
}
TABLE PKB::getUsesPEntEnt() {
	return PKBUses::getUsesPEntEnt();
}


////////////////////////////////////
// CallTable APIs
////////////////////////////////////

void PKB::setCallProc(PROC_NAME caller, PROC_NAME callee) {
	 PKBCall::setCallProc(caller, callee);
}

void PKB::setCallStmt(STMT_NO stmtNo, PROC_NAME procName) {
	 PKBCall::setCallStmt(stmtNo, procName);
};

void PKB::setCallT(PROC_NAME caller, PROC_NAME callee) {
	 PKBCall::setCallTProc(caller, callee);
};

TABLE PKB::getCallStmtTable() {
	return PKBCall::getCallStmtTable();
}


PROC_NAME PKB::getCallProcByStmt(STMT_NO stmtNo) {
	return PKBCall::getCallProcByStmt(stmtNo);
}

//Call Bool Evaluation
bool PKB::isCallsAnyAny() {
	return PKBCall::isCallsAnyAny();
}
bool PKB::isCallsAnyIdent(PROC_NAME p2) {
	return PKBCall::isCallsAnyIdent(p2);
}
bool PKB::isCallsIdentAny(PROC_NAME p1) {
	return PKBCall::isCallsIdentAny(p1);
}
bool PKB::isCallsIdentIdent(PROC_NAME p1, PROC_NAME p2) {
	return PKBCall::isCallsIdentIdent(p1,p2);
}

bool PKB::isCallsTAnyAny() {
	return PKBCall::isCallsTAnyAny();
}
bool PKB::isCallsTAnyIdent(PROC_NAME p2) {
	return PKBCall::isCallsTAnyIdent(p2);
}
bool PKB::isCallsTIdentAny(PROC_NAME p1) {
	return PKBCall::isCallsTIdentAny(p1);
}
bool PKB::isCallsTIdentIdent(PROC_NAME p1, PROC_NAME p2) {
	return PKBCall::isCallsTIdentIdent(p1,p2);
}

//Call Table Evaluation
TABLE PKB::getCallsAnyEnt() {
	return PKBCall::getCallsAnyEnt();
}
TABLE PKB::getCallsIdentEnt(PROC_NAME p1) {
	return PKBCall::getCallsIdentEnt(p1);
}
TABLE PKB::getCallsEntAny() {
	return PKBCall::getCallsEntAny();
}
TABLE PKB::getCallsEntIdent(PROC_NAME p2) {
	return PKBCall::getCallsEntIdent(p2);
}
TABLE PKB::getCallsEntEnt() {
	return PKBCall::getCallsEntEnt();
}

TABLE PKB::getCallsTAnyEnt() {
	return PKBCall::getCallsTAnyEnt();
}
TABLE PKB::getCallsTIdentEnt(PROC_NAME p1) {
	return PKBCall::getCallsTIdentEnt(p1);
}
TABLE PKB::getCallsTEntAny() {
	return PKBCall::getCallsTEntAny();
}
TABLE PKB::getCallsTEntIdent(PROC_NAME p2) {
	return PKBCall::getCallsTEntIdent(p2);
}
TABLE PKB::getCallsTEntEnt() {
	return PKBCall::getCallsTEntEnt();
}

//////////////////////////////////
//Pattern
//////////////////////////////////

void PKB::setIfPattern(STMT_NO stmtNo, VAR_NAME varName) {
	 PKBPattern::setIfPattern(stmtNo, varName);
}
void PKB::setWhilePattern(STMT_NO stmtNo, VAR_NAME varName) {
	 PKBPattern::setWhilePattern(stmtNo, varName);
}
void PKB::setAssignPattern(STMT_NO stmtNo, EXPR_SPEC pattern) {
	 PKBPattern::setAssignPattern(stmtNo, pattern);
}

STMT_LIST PKB::getPatternIfAny() {
	return PKBPattern::getPatternIfAny();
}
STMT_LIST PKB::getPatternIfIdent(VAR_NAME varName) {
	return PKBPattern::getPatternIfIdent(varName);
}
TABLE PKB::getPatternIfEnt() {
	return PKBPattern::getPatternIfEnt();
}

STMT_LIST PKB::getPatternWhileAny() {
	return PKBPattern::getPatternWhileAny();
}
STMT_LIST PKB::getPatternWhileIdent(VAR_NAME varName) {
	return PKBPattern::getPatternWhileIdent(varName);
}
TABLE PKB::getPatternWhileEnt() {
	return PKBPattern::getPatternWhileEnt();
}

TABLE PKB::getPatternAssignAnyAny() {
	return PKBPattern::getPatternAssignAnyAny();
}
TABLE PKB::getPatternAssignAnyPartial(EXPR_SPEC expression) {
	return PKBPattern::getPatternAssignAnyPartial(expression);
}
TABLE PKB::getPatternAssignAnyFull(EXPR_SPEC expression) {
	return PKBPattern::getPatternAssignAnyFull(expression);
}
TABLE PKB::getPatternAssignIdentAny(VAR_NAME varName) {
	return PKBPattern::getPatternAssignIdentAny(varName);
}
TABLE PKB::getPatternAssignIdentPartial(VAR_NAME varName, EXPR_SPEC expression) {
	return PKBPattern::getPatternAssignIdentPartial(varName, expression);
}
TABLE PKB::getPatternAssignIdentFull(VAR_NAME varName, EXPR_SPEC expression) {
	return PKBPattern::getPatternAssignIdentFull(varName, expression);
}
TABLE PKB::getPatternAssignEntAny() {
	return PKBPattern::getPatternAssignEntAny();
}
TABLE PKB::getPatternAssignEntPartial(EXPR_SPEC expression) {
	return PKBPattern::getPatternAssignEntPartial(expression);
}
TABLE PKB::getPatternAssignEntFull(EXPR_SPEC expression) {
	return PKBPattern::getPatternAssignEntFull(expression);
}

////////////////////////////////////
// NextTable APIs
////////////////////////////////////

void PKB::setNext(PROG_LINE n1, PROG_LINE n2) {
	 PKBNext::setNext(n1, n2);
};

void PKB::setNextT(PROG_LINE n1, PROG_LINE n2) {
	 PKBNext::setNextT(n1, n2);
};

void PKB::setNextBip(PROG_LINE n1, PROG_LINE n2) {
	 PKBNext::setNextBip(n1, n2);
};

void PKB::setNextBipT(PROG_LINE n1, PROG_LINE n2) {
	 PKBNext::setNextBipT(n1, n2);
};

//Next Bool Evaluation
bool PKB::isNextAnyAny() {
	return PKBNext::isNextAnyAny();
}
bool PKB::isNextAnyIdent(PROG_LINE n2) {
	return PKBNext::isNextAnyIdent(n2);
}
bool PKB::isNextIdentAny(PROG_LINE n1) {
	return PKBNext::isNextIdentAny(n1);
}
bool PKB::isNextIdentIdent(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextIdentIdent(n1,n2);
}

bool PKB::isNextT(PROG_LINE nextByLine, PROG_LINE nextLine) {
	return PKBNext::isNextT(nextByLine, nextLine);
}

bool PKB::isNextTAnyAny() {
	return PKBNext::isNextTAnyAny();
}
bool PKB::isNextTAnyIdent(PROG_LINE n2) {
	return PKBNext::isNextTAnyIdent(n2);
}
bool PKB::isNextTIdentAny(PROG_LINE n1) {
	return PKBNext::isNextTIdentAny(n1);
}
bool PKB::isNextTIdentIdent(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextTIdentIdent(n1,n2);
}

bool PKB::isNextBipAnyAny() {
	return PKBNext::isNextBipAnyAny();
}
bool PKB::isNextBipAnyIdent(PROG_LINE n2) {
	return PKBNext::isNextBipAnyIdent(n2);
}
bool PKB::isNextBipIdentAny(PROG_LINE n1) {
	return PKBNext::isNextBipIdentAny(n1);
}
bool PKB::isNextBipIdentIdent(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextBipIdentIdent(n1, n2);
}

bool PKB::isNextBipTAnyAny() {
	return PKBNext::isNextBipTAnyAny();
}
bool PKB::isNextBipTAnyIdent(PROG_LINE n2) {
	return PKBNext::isNextBipTAnyIdent(n2);
}
bool PKB::isNextBipTIdentAny(PROG_LINE n1) {
	return PKBNext::isNextBipTIdentAny(n1);
}
bool PKB::isNextBipTIdentIdent(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextBipTIdentIdent(n1, n2);
}

//Next Table Evaluation
TABLE PKB::getNextAnyEnt(STMT_TYPE stmtType) {
	return PKBNext::getNextAnyEnt(stmtType);
}
TABLE PKB::getNextIdentEnt(PROG_LINE n1, STMT_TYPE stmtType) {
	return PKBNext::getNextIdentEnt(n1, stmtType);
}
TABLE PKB::getNextEntAny(STMT_TYPE stmtType) {
	return PKBNext::getNextEntAny(stmtType);
}
TABLE PKB::getNextEntIdent(STMT_TYPE stmtType, PROG_LINE n2) {
	return PKBNext::getNextEntIdent(stmtType, n2);
}
TABLE PKB::getNextEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2) {
	return PKBNext::getNextEntEnt(stmtType1, stmtType2);
}

TABLE PKB::getNextTAnyEnt(STMT_TYPE stmtType) {
	return PKBNext::getNextTAnyEnt(stmtType);
}
TABLE PKB::getNextTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType) {
	return PKBNext::getNextTIdentEnt(n1, stmtType);
}
TABLE PKB::getNextTEntAny(STMT_TYPE stmtType) {
	return PKBNext::getNextTEntAny(stmtType);
}
TABLE PKB::getNextTEntIdent(STMT_TYPE stmtType, PROG_LINE n2) {
	return PKBNext::getNextTEntIdent(stmtType, n2);
}
TABLE PKB::getNextTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2) {
	return PKBNext::getNextTEntEnt(stmtType1, stmtType2);
}
TABLE PKB::getNextTSelf(STMT_TYPE stmtType) {
	return PKBNext::getNextTSelf(stmtType);
}

TABLE PKB::getNextBipAnyEnt(STMT_TYPE stmtType) {
	return PKBNext::getNextBipAnyEnt(stmtType);
}
TABLE PKB::getNextBipIdentEnt(PROG_LINE n1, STMT_TYPE stmtType) {
	return PKBNext::getNextBipIdentEnt(n1, stmtType);
}
TABLE PKB::getNextBipEntAny(STMT_TYPE stmtType) {
	return PKBNext::getNextBipEntAny(stmtType);
}
TABLE PKB::getNextBipEntIdent(STMT_TYPE stmtType, PROG_LINE n2) {
	return PKBNext::getNextBipEntIdent(stmtType, n2);
}
TABLE PKB::getNextBipEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2) {
	return PKBNext::getNextBipEntEnt(stmtType1, stmtType2);
}

TABLE PKB::getNextBipTAnyEnt(STMT_TYPE stmtType) {
	return PKBNext::getNextBipTAnyEnt(stmtType);
}
TABLE PKB::getNextBipTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType) {
	return PKBNext::getNextBipTIdentEnt(n1, stmtType);
}
TABLE PKB::getNextBipTEntAny(STMT_TYPE stmtType) {
	return PKBNext::getNextBipTEntAny(stmtType);
}
TABLE PKB::getNextBipTEntIdent(STMT_TYPE stmtType, PROG_LINE n2) {
	return PKBNext::getNextBipTEntIdent(stmtType, n2);
}
TABLE PKB::getNextBipTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2) {
	return PKBNext::getNextBipTEntEnt(stmtType1, stmtType2);
}
TABLE PKB::getNextBipTSelf(STMT_TYPE stmtType) {
	return PKBNext::getNextBipTSelf(stmtType);
}

//////////////////////////////////
//Affects
//////////////////////////////////

void PKB::setAffects(STMT_NO a1, STMT_NO a2) {
	 PKBAffects::setAffects(a1, a2);
}
void PKB::setAffectsT(STMT_NO a1, STMT_NO a2) {
	 PKBAffects::setAffectsT(a1, a2);
}
void PKB::setAffectsBip(STMT_NO a1, STMT_NO a2) {
	 PKBAffects::setAffectsBip(a1, a2);
}
void PKB::setAffectsBipT(STMT_NO a1, STMT_NO a2) {
	 PKBAffects::setAffectsBipT(a1, a2);
}

bool PKB::isAffectsAnyAny() {
	return PKBAffects::isAffectsAnyAny();
}
bool PKB::isAffectsAnyIdent(STMT_NO a2) {
	return PKBAffects::isAffectsAnyIdent(a2);
}
bool PKB::isAffectsIdentAny(STMT_NO a1) {
	return PKBAffects::isAffectsIdentAny(a1);
}
bool PKB::isAffectsIdentIdent(STMT_NO a1, STMT_NO a2) {
	return PKBAffects::isAffectsIdentIdent(a1,a2);
}

bool PKB::isAffectsTAnyAny() {
	return PKBAffects::isAffectsTAnyAny();
}
bool PKB::isAffectsTAnyIdent(STMT_NO a2) {
	return PKBAffects::isAffectsTAnyIdent(a2);
}
bool PKB::isAffectsTIdentAny(STMT_NO a1) {
	return PKBAffects::isAffectsTIdentAny(a1);
}
bool PKB::isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2) {
	return PKBAffects::isAffectsTIdentIdent(a1,a2);
}

bool PKB::isAffectsBipAnyAny() {
	return PKBAffects::isAffectsBipAnyAny();
}
bool PKB::isAffectsBipAnyIdent(STMT_NO a2) {
	return PKBAffects::isAffectsBipAnyIdent(a2);
}
bool PKB::isAffectsBipIdentAny(STMT_NO a1) {
	return PKBAffects::isAffectsBipIdentAny(a1);
}
bool PKB::isAffectsBipIdentIdent(STMT_NO a1, STMT_NO a2) {
	return PKBAffects::isAffectsBipIdentIdent(a1, a2);
}

bool PKB::isAffectsBipTAnyAny() {
	return PKBAffects::isAffectsBipTAnyAny();
}
bool PKB::isAffectsBipTAnyIdent(STMT_NO a2) {
	return PKBAffects::isAffectsBipTAnyIdent(a2);
}
bool PKB::isAffectsBipTIdentAny(STMT_NO a1) {
	return PKBAffects::isAffectsBipTIdentAny(a1);
}
bool PKB::isAffectsBipTIdentIdent(STMT_NO a1, STMT_NO a2) {
	return PKBAffects::isAffectsBipTIdentIdent(a1, a2);
}

//Affects Table Evaluation
TABLE PKB::getAffectsAnyEnt() {
	return PKBAffects::getAffectsAnyEnt();
}
TABLE PKB::getAffectsIdentEnt(STMT_NO a1) {
	return PKBAffects::getAffectsIdentEnt(a1);
}
TABLE PKB::getAffectsEntAny() {
	return PKBAffects::getAffectsEntAny();
}
TABLE PKB::getAffectsEntIdent(STMT_NO a2) {
	return PKBAffects::getAffectsEntIdent(a2);
}
TABLE PKB::getAffectsEntEnt() {
	return PKBAffects::getAffectsEntEnt();
}
TABLE PKB::getAffectsSelf() {
	return PKBAffects::getAffectsSelf();
}

TABLE PKB::getAffectsTAnyEnt() {
	return PKBAffects::getAffectsTAnyEnt();
}
TABLE PKB::getAffectsTIdentEnt(STMT_NO a1) {
	return PKBAffects::getAffectsTIdentEnt(a1);
}
TABLE PKB::getAffectsTEntAny() {
	return PKBAffects::getAffectsTEntAny();
}
TABLE PKB::getAffectsTEntIdent(STMT_NO a2) {
	return PKBAffects::getAffectsTEntIdent(a2);
}
TABLE PKB::getAffectsTEntEnt() {
	return PKBAffects::getAffectsTEntEnt();
}
TABLE PKB::getAffectsTSelf() {
	return PKBAffects::getAffectsTSelf();
}

TABLE PKB::getAffectsBipAnyEnt() {
	return PKBAffects::getAffectsBipAnyEnt();
}
TABLE PKB::getAffectsBipIdentEnt(STMT_NO a1) {
	return PKBAffects::getAffectsBipIdentEnt(a1);
}
TABLE PKB::getAffectsBipEntAny() {
	return PKBAffects::getAffectsBipEntAny();
}
TABLE PKB::getAffectsBipEntIdent(STMT_NO a2) {
	return PKBAffects::getAffectsBipEntIdent(a2);
}
TABLE PKB::getAffectsBipEntEnt() {
	return PKBAffects::getAffectsBipEntEnt();
}
TABLE PKB::getAffectsBipSelf() {
	return PKBAffects::getAffectsBipSelf();
}

TABLE PKB::getAffectsBipTAnyEnt() {
	return PKBAffects::getAffectsBipTAnyEnt();
}
TABLE PKB::getAffectsBipTIdentEnt(STMT_NO a1) {
	return PKBAffects::getAffectsBipTIdentEnt(a1);
}
TABLE PKB::getAffectsBipTEntAny() {
	return PKBAffects::getAffectsBipTEntAny();
}
TABLE PKB::getAffectsBipTEntIdent(STMT_NO a2) {
	return PKBAffects::getAffectsBipTEntIdent(a2);
}
TABLE PKB::getAffectsBipTEntEnt() {
	return PKBAffects::getAffectsBipTEntEnt();
}
TABLE PKB::getAffectsBipTSelf() {
	return PKBAffects::getAffectsBipTSelf();
}




//////////////////////////////////
//Attributes
//////////////////////////////////

STMT_LIST PKB::getWithIdentAttr(IDENT iden, ENT_TYPE ent, ATTR attr) {
	return PKBWith::getWithIdentAttr(iden, ent, attr);
}
STMT_LIST PKB::getWithIdentLine(PROG_LINE n) {
	return PKBWith::getWithIdentLine(n);
}
TABLE PKB::getWithAttrAttr(ENT_TYPE ent1, ATTR attr1, ENT_TYPE ent2, ATTR attr2) {
	return PKBWith::getWithAttrAttr(ent1, attr1, ent2, attr2);
}
TABLE PKB::getWithAttrLine(ENT_TYPE ent, ATTR attr) {
	return PKBWith::getWithAttrLine(ent, attr);
}
TABLE PKB::getWithLineLine() {
	return PKBWith::getWithLineLine();
}

IDENT PKB::getAttribute(IDENT iden, ENT_TYPE ent, ATTR attr) {
	if (ent == "call" && attr == "procName") {
		return PKBCall::getCallProcByStmt(iden);
	}
	else if (ent == "print" && attr == "varName") {
		return PKBPrint::getPrintVariable(iden);
	}
	else if (ent == "read" && attr == "varName") {
		return PKBRead::getReadVariable(iden);
	}
	else {
		return iden;
	}
}
