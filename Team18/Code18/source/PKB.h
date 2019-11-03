#pragma once
#include "AbstractType.h"

class PKB {

public:
	
	// Clear PKB database
	static bool clear();
	static bool clearTempPKB();

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
	static bool setProcByStmt(STMT_NO stmtNo, PROC_NAME proc);
	static PROC_NAME getProcByStmt(STMT_NO stmtNo);
	static bool setProcedure(PROC_NAME procName, STMT_NO start, STMT_LIST end);

	//Print Functions
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_LIST getAllPrintVar();

	//Read Functions
	static bool setRead(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_LIST getAllReadVar();

	//Constant Functions
	static bool setConstant( CONST_VAL constantVal);
	static CONST_LIST getConstants();

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
	static PROC_LIST getAllCallProc();
	static PROC_NAME getCallProcByStmt(STMT_NO stmtNo);

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

	static bool isNextBipAnyAny();
	static bool isNextBipAnyIdent(PROG_LINE n2);
	static bool isNextBipIdentAny(PROG_LINE n1);
	static bool isNextBipIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static bool isNextBipTAnyAny();
	static bool isNextBipTAnyIdent(PROG_LINE n2);
	static bool isNextBipTIdentAny(PROG_LINE n1);
	static bool isNextBipTIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static TABLE getNextAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextEntAny(STMT_TYPE stmtType);
	static TABLE getNextEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static TABLE getNextTAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextTEntAny(STMT_TYPE stmtType);
	static TABLE getNextTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static TABLE getNextTSelf(STMT_TYPE stmtType);

	static TABLE getNextBipAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextBipIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextBipEntAny(STMT_TYPE stmtType);
	static TABLE getNextBipEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static TABLE getNextBipTAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextBipTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextBipTEntAny(STMT_TYPE stmtType);
	static TABLE getNextBipTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static TABLE getNextBipTSelf(STMT_TYPE stmtType);

	//Pattern 
	static bool setIfPattern(STMT_NO stmtNo, VAR_NAME varName);
	static bool setWhilePattern(STMT_NO stmtNo, VAR_NAME varName);
	static bool setAssignPattern(STMT_NO stmtNo, EXPR_SPEC pattern);

	//Pattern Evaluation
	static STMT_LIST getPatternIfAny();
	static STMT_LIST getPatternIfIdent(VAR_NAME varName);
	static TABLE getPatternIfEnt();

	static STMT_LIST getPatternWhileAny();
	static STMT_LIST getPatternWhileIdent(VAR_NAME varName);
	static TABLE getPatternWhileEnt();

	static TABLE getPatternAssignAnyAny();
	static TABLE getPatternAssignAnyPartial(EXPR_SPEC expression);
	static TABLE getPatternAssignAnyFull(EXPR_SPEC expression);
	static TABLE getPatternAssignIdentAny(VAR_NAME varName);
	static TABLE getPatternAssignIdentPartial(VAR_NAME varName, EXPR_SPEC expression);
	static TABLE getPatternAssignIdentFull(VAR_NAME varName, EXPR_SPEC expression);
	static TABLE getPatternAssignEntAny();
	static TABLE getPatternAssignEntPartial(EXPR_SPEC expression);
	static TABLE getPatternAssignEntFull(EXPR_SPEC expression);

	//Affects

	//Affects Bool Evaluation
	static bool isAffectsAnyAny();
	static bool isAffectsAnyIdent(STMT_NO a2);
	static bool isAffectsIdentAny(STMT_NO a1);
	static bool isAffectsIdentIdent(STMT_NO a1, STMT_NO a2);

	static bool isAffectsTAnyAny();
	static bool isAffectsTAnyIdent(STMT_NO a2);
	static bool isAffectsTIdentAny(STMT_NO a1);
	static bool isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2);

	//Affects Table Evaluation
	static TABLE getAffectsAnyEnt();
	static TABLE getAffectsIdentEnt(STMT_NO a1);
	static TABLE getAffectsEntAny();
	static TABLE getAffectsEntIdent(STMT_NO a2);
	static TABLE getAffectsEntEnt();
	static TABLE getAffectsSelf();

	static TABLE getAffectsTAnyEnt();
	static TABLE getAffectsTIdentEnt(STMT_NO a1);
	static TABLE getAffectsTEntAny();
	static TABLE getAffectsTEntIdent(STMT_NO a2);
	static TABLE getAffectsTEntEnt();
	static TABLE getAffectsTSelf();

	//with Clause
	static STMT_LIST getWithIdentAttr(IDENT iden, ENT_TYPE ent, ATTR attr);
	static STMT_LIST getWithIdentLine(IDENT iden);
	static TABLE getWithAttrAttr(ENT_TYPE ent1, ATTR attr1, ENT_TYPE ent2, ATTR attr2);
	static TABLE getWithAttrLine(ENT_TYPE ent, ATTR attr);
	static TABLE getWithLineLine();

	//Attributes
	static IDENT getAttribute(IDENT iden, ENT_TYPE ent, ATTR attr);
};
