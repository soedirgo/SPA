#include "PKBWith.h"
#include "PKBStmt.h"
#include "PKBConstant.h"
#include "PKBVariable.h"
#include "PKBProcedure.h"
#include "PKBCall.h"
#include "PKBRead.h"
#include "PKBPrint.h"
using namespace std;

ENT_LIST PKBWith::getWithIdentAttr(IDENT iden, ENT_TYPE ent, ATTR attr) {
	ENT_LIST resultTable;
	TABLE list;
	if (ent == "procedure") {
		list = PKBProcedure::getProcedures();
	}
	else if (ent == "call" && attr == "procName") {
		list = PKBCall ::getAllCalleeProc();
	}
	else if (ent == "variable") {
		list = PKBVariable::getVariables();
	}
	else if (ent == "read" && attr == "varName") {
		list = PKBRead::getAllReadVar();
	}
	else if (ent == "print" && attr == "varName") {
		list = PKBPrint::getAllPrintVar();
	}
	else if (ent == "constant") {
		list = PKBConstant::getConstants();
	}
	else {
		if (ent == "stmt") {
			list = PKBStmt::getStmts();
		}
		else if ((ent == "read" || ent == "print"  || ent == "call" || ent == "while" 
			|| ent == "if" || ent == "assign") && attr == "stmt#") {
			list = PKBStmt::getStmtsByType(ent);
		}
		else {
			return resultTable;
		}
	}
	for (auto vectorIter : list) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == iden) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBWith::getWithIdentLine(IDENT iden) {
	STMT_LIST resultTable;
	TABLE list = PKBStmt::getStmts();
	for (auto vectorIter : list) {
		if (vectorIter.front() == iden) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBWith::getWithAttrAttr(ENT_TYPE ent1, ATTR attr1, ENT_TYPE ent2, ATTR attr2) {
	TABLE resultTable;
	TABLE list1, list2;
	if (ent1 == "procedure") {
		list1 = PKBProcedure::getProcedures();
	}
	else if (ent1 == "call" && attr1 == "procName") {
		list1 = PKBCall::getAllCalleeProc();
	}
	else if (ent1 == "variable") {
		list1 = PKBVariable::getVariables();
	}
	else if (ent1 == "read" && attr1 == "varName") {
		list1 = PKBRead::getAllReadVar();
	}
	else if (ent1 == "print" && attr1 == "varName") {
		list1 = PKBPrint::getAllPrintVar();
	}
	else if (ent1 == "constant") {
		list1 = PKBConstant::getConstants();
	}
	else {
		if (ent1 == "stmt") {
			list1 = PKBStmt::getStmts();
		}
		else if (attr1 == "stmt#") {
			list1 = PKBStmt::getStmtsByType(ent1);
		}
		else {
			return resultTable;
		}
	}
	if (ent2 == "procedure") {
		list2 = PKBProcedure::getProcedures();
	}
	else if (ent2 == "call" && attr2 == "procName") {
		list2 = PKBCall::getAllCalleeProc();
	}
	else if (ent2 == "variable") {
		list2 = PKBVariable::getVariables();
	}
	else if (ent2 == "read" && attr2 == "varName") {
		list2 = PKBRead::getAllReadVar();
	}
	else if (ent2 == "print" && attr2 == "varName") {
		list2 = PKBPrint::getAllPrintVar();
	}
	else if (ent2 == "constant") {
		list2 = PKBConstant::getConstants();
	}
	else {
		if (ent2 == "stmt") {
			list2 = PKBStmt::getStmts();
		}
		else if (attr2 == "stmt#") {
			list2 = PKBStmt::getStmtsByType(ent2);
		}
		else {
			return resultTable;
		}
	}
	for (auto vectorIter1 : list1) {
		for (auto vectorIter2 : list2) {
			if (vectorIter1.front() == vectorIter2.front()) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter1.front());
				tuple.push_back(vectorIter2.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBWith::getWithAttrLine(ENT_TYPE ent, ATTR attr) {
	TABLE resultTable;
	TABLE list1, list2;
	list2 = PKBStmt::getStmts();
	if (ent == "constant") {
		list1 = PKBConstant::getConstants();
	}
	else {
		if (ent == "stmt") {
			list1 = PKBStmt::getStmts();
		}
		else if ((ent == "read" || ent == "print" || ent == "call" || ent == "while"
			|| ent == "if" || ent == "assign") && attr == "stmt#") {
			list1 = PKBStmt::getStmtsByType(ent);
		}
		else {
			return resultTable;
		}
	}
	for (auto vectorIter1 : list1) {
		for (auto vectorIter2 : list2) {
			if (vectorIter1.front() == vectorIter2.front()) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter1.front());
				tuple.push_back(vectorIter2.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBWith::getWithLineLine() {
	TABLE resultTable;
	TABLE list1, list2;
	list1 = PKBStmt::getStmts();
	list2 = PKBStmt::getStmts();
	for (auto vectorIter1 : list1) {
		for (auto vectorIter2 : list2) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter1.front());
			tuple.push_back(vectorIter2.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}


