#pragma once
#include "AbstractType.h"

class PKB {

public:
	
	// Clear PKB database
	static void clear();
	static bool clearTempPKB();

	//////////////////////////////////
	//Variable Functions
	//////////////////////////////////

	//Set variable into PKB
	static bool setVariable(VAR_NAME varName);
	//Get all variables from PKB
	static LIST_OF_VARIABLE_NAME getVariables();

	//////////////////////////////////
	//Stmt Functions
	//////////////////////////////////

	//Set StmtNo to PKB
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);

	//Get STMT_LIST from PKB
	static STMT_LIST getStmts();
	static STMT_LIST getPrints();
	static STMT_LIST getReads();
	static STMT_LIST getAssigns();
	static STMT_LIST getWhiles();
	static STMT_LIST getIfs();
	static STMT_LIST getCalls();
	static STMT_LIST getProgLines();

	static STMT_LIST getStmtsByType(STMT_TYPE type);
	static STMT_TYPE getTypeByStmtNo(STMT_NO stmtNo);

	//////////////////////////////////
	//Procedure Functions
	//////////////////////////////////
	static LIST_OF_PROC_NAME getProcedures();
	static bool setProcByStmt(STMT_NO stmtNo, PROC_NAME proc);
	static bool setProcedure(PROC_NAME procName, STMT_NO start, STMT_LIST end);
	static PROC_NAME getProcByStmt(STMT_NO stmtNo);
	static STMT_LIST getProcedureStartEnd(PROC_NAME procName);

	//////////////////////////////////
	//Print Functions
	//////////////////////////////////
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getAllPrintVar();

	//////////////////////////////////
	//Read Functions
	//////////////////////////////////
	static bool setRead(STMT_NO stmtNo, VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getAllReadVar();

	//////////////////////////////////
	//Constant Functions
	//////////////////////////////////
	static bool setConstant( CONST_VAL constantVal);
	static LIST_OF_CONS_VAL getConstants();

	//////////////////////////////////
	//Follow Functions
	//////////////////////////////////
	static bool setFollows(STMT_NO followedBy, STMT_NO follow);
	static bool setFollowsT(STMT_NO followedBy, STMT_NO follow);

	static STMT_NO getFollowsStmt(STMT_NO followedBy);

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
	static STMT_LIST getFollowsAnyEnt(STMT_TYPE s2);
	static STMT_LIST getFollowsIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getFollowsEntAny(STMT_TYPE s1);
	static STMT_LIST getFollowsEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static STMT_LIST getFollowsTAnyEnt(STMT_TYPE s2);
	static STMT_LIST getFollowsTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getFollowsTEntAny(STMT_TYPE s1);
	static STMT_LIST getFollowsTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsTEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	//////////////////////////////////
	//Parent Functions
	//////////////////////////////////
	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentT(STMT_NO parent, STMT_NO child);
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
	static STMT_LIST getParentAnyEnt(STMT_TYPE s2);
	static STMT_LIST getParentIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getParentEntAny(STMT_TYPE s1);
	static STMT_LIST getParentEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static STMT_LIST getParentTAnyEnt(STMT_TYPE s2);
	static STMT_LIST getParentTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getParentTEntAny(STMT_TYPE s1);
	static STMT_LIST getParentTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentTEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	//////////////////////////////////
	//Modifies Function
	//////////////////////////////////
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
	static LIST_OF_VARIABLE_NAME getModifiesSIdentEnt(STMT_NO stmtNo);
	static TABLE getModifiesSEntEnt(STMT_TYPE type);

	static LIST_OF_PROC_NAME getModifiesPEntAny();
	static LIST_OF_PROC_NAME getModifiesPEntIdent(VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getModifiesPIdentEnt(PROC_NAME procName);
	static TABLE getModifiesPEntEnt();

	//////////////////////////////////
	//Uses Function
	//////////////////////////////////
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
	static LIST_OF_VARIABLE_NAME getUsesSIdentEnt(STMT_NO stmtNo);
	static TABLE getUsesSEntEnt(STMT_TYPE type);

	static LIST_OF_PROC_NAME getUsesPEntAny();
	static LIST_OF_PROC_NAME getUsesPEntIdent(VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getUsesPIdentEnt(PROC_NAME procName);
	static TABLE getUsesPEntEnt();

	//////////////////////////////////
	//Call Function
	//////////////////////////////////
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME procName);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallT(PROC_NAME caller, PROC_NAME callee);
	static PROC_NAME getCallProcByStmt(STMT_NO stmtNo);
	static TABLE getCallStmtTable();

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
	static LIST_OF_PROC_NAME getCallsAnyEnt();
	static LIST_OF_PROC_NAME getCallsIdentEnt(PROC_NAME p1);
	static LIST_OF_PROC_NAME getCallsEntAny();
	static LIST_OF_PROC_NAME getCallsEntIdent(PROC_NAME p2);
	static TABLE getCallsEntEnt();

	static LIST_OF_PROC_NAME getCallsTAnyEnt();
	static LIST_OF_PROC_NAME getCallsTIdentEnt(PROC_NAME p1);
	static LIST_OF_PROC_NAME getCallsTEntAny();
	static LIST_OF_PROC_NAME getCallsTEntIdent(PROC_NAME p2);
	static TABLE getCallsTEntEnt();

	//////////////////////////////////
	//Pattern 
	//////////////////////////////////
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

	static STMT_LIST getPatternAssignAnyAny();
	static STMT_LIST getPatternAssignAnyPartial(EXPR_SPEC expression);
	static STMT_LIST getPatternAssignAnyFull(EXPR_SPEC expression);
	static STMT_LIST getPatternAssignIdentAny(VAR_NAME varName);
	static STMT_LIST getPatternAssignIdentPartial(VAR_NAME varName, EXPR_SPEC expression);
	static STMT_LIST getPatternAssignIdentFull(VAR_NAME varName, EXPR_SPEC expression);
	static TABLE getPatternAssignEntAny();
	static TABLE getPatternAssignEntPartial(EXPR_SPEC expression);
	static TABLE getPatternAssignEntFull(EXPR_SPEC expression);

	//////////////////////////////////
	//Next Function
	//////////////////////////////////
	static bool setNext(PROG_LINE n1, PROG_LINE n2);
	static bool setNextT(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextBip(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextBipT(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool isNextT(PROG_LINE nextByLine, PROG_LINE nextLine);
	
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

	static LINE_LIST getNextAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static LINE_LIST getNextTAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextTEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static TABLE getNextTSelf(STMT_TYPE stmtType);

	static LINE_LIST getNextBipAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextBipIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextBipEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextBipEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static LINE_LIST getNextBipTAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextBipTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextBipTEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextBipTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static TABLE getNextBipTSelf(STMT_TYPE stmtType);

	//////////////////////////////////
	//Affects
	//////////////////////////////////

	static bool setAffects(STMT_NO a1, STMT_NO a2);
	static bool setAffectsT(STMT_NO a1, STMT_NO a2);
	static bool setAffectsBip(STMT_NO a1, STMT_NO a2);
	static bool setAffectsBipT(STMT_NO a1, STMT_NO a2);

	//Affects Bool Evaluation
	static bool isAffectsAnyAny();
	static bool isAffectsAnyIdent(STMT_NO a2);
	static bool isAffectsIdentAny(STMT_NO a1);
	static bool isAffectsIdentIdent(STMT_NO a1, STMT_NO a2);

	static bool isAffectsTAnyAny();
	static bool isAffectsTAnyIdent(STMT_NO a2);
	static bool isAffectsTIdentAny(STMT_NO a1);
	static bool isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2);

	static bool isAffectsBipAnyAny();
	static bool isAffectsBipAnyIdent(STMT_NO a2);
	static bool isAffectsBipIdentAny(STMT_NO a1);
	static bool isAffectsBipIdentIdent(STMT_NO a1, STMT_NO a2);

	static bool isAffectsBipTAnyAny();
	static bool isAffectsBipTAnyIdent(STMT_NO a2);
	static bool isAffectsBipTIdentAny(STMT_NO a1);
	static bool isAffectsBipTIdentIdent(STMT_NO a1, STMT_NO a2);

	//Affects Table Evaluation
	static STMT_LIST getAffectsAnyEnt();
	static STMT_LIST getAffectsIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsEntAny();
	static STMT_LIST getAffectsEntIdent(STMT_NO a2);
	static TABLE getAffectsEntEnt();
	static STMT_LIST getAffectsSelf();

	static STMT_LIST getAffectsTAnyEnt();
	static STMT_LIST getAffectsTIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsTEntAny();
	static STMT_LIST getAffectsTEntIdent(STMT_NO a2);
	static TABLE getAffectsTEntEnt();
	static STMT_LIST getAffectsTSelf();

	static STMT_LIST getAffectsBipAnyEnt();
	static STMT_LIST getAffectsBipIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsBipEntAny();
	static STMT_LIST getAffectsBipEntIdent(STMT_NO a2);
	static TABLE getAffectsBipEntEnt();
	static STMT_LIST getAffectsBipSelf();

	static STMT_LIST getAffectsBipTAnyEnt();
	static STMT_LIST getAffectsBipTIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsBipTEntAny();
	static STMT_LIST getAffectsBipTEntIdent(STMT_NO a2);
	static TABLE getAffectsBipTEntEnt();
	static STMT_LIST getAffectsBipTSelf();

	//////////////////////////////////
	//with Clause
	//////////////////////////////////
	static STMT_LIST getWithIdentAttr(IDENT iden, ENT_TYPE ent, ATTR attr);
	static STMT_LIST getWithIdentLine(IDENT iden);
	static TABLE getWithAttrAttr(ENT_TYPE ent1, ATTR attr1, ENT_TYPE ent2, ATTR attr2);
	static TABLE getWithAttrLine(ENT_TYPE ent, ATTR attr);
	static TABLE getWithLineLine();
	
	//////////////////////////////////
	//Attributes
	//////////////////////////////////
	static IDENT getAttribute(IDENT iden, ENT_TYPE ent, ATTR attr);
};
