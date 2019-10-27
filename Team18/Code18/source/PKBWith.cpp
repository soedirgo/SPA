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
	if (ent == "procedure" && attr == "procName") {
		list = PKBProcedure::getProcedures();
	}
	else if (ent == "call" && attr == "procName") {
		list = PKBCall ::getCallStmtTable();
	}
	else if (ent == "variable" && attr == "varName") {
		list = PKBVariable::getVariables();
	}
	else if (ent == "read" && attr == "varName") {
		list = PKBRead::getAllReadVar();
	}
	else if (ent == "print" && attr == "varName") {
		list = PKBPrint::getAllPrintVar();
	}
	else if (ent == "constant" && attr == "value") {
		list = PKBConstant::getConstants();
	}
	else if (ent == "stmt" && attr == "stmt#") {
		list = PKBStmt::getStmts();
	}
	else if ((ent == "read" || ent == "print"  || ent == "call" || ent == "while" 
		|| ent == "if" || ent == "assign") && attr == "stmt#") {
		list = PKBStmt::getStmtsByType(ent);
	}
	else {
		return resultTable;
	}

	if ((ent == "read" && attr == "varName") || (ent == "print" && attr == "varName") || (ent == "call" && attr == "procName")) {
		for (auto vectorIter : list) {
			vector<string> tuple = vector<string>();
				if (vectorIter.back() == iden) {
					tuple.push_back(vectorIter.front());
						resultTable.emplace(tuple);
				}
		}
	}
	else {
		for (auto vectorIter : list) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == iden) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
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
	if (ent1 == "procedure" && attr1 == "procName") {
		list1 = PKBProcedure::getProcedures();
	}
	else if (ent1 == "call" && attr1 == "procName") {
		list1 = PKBCall::getCallStmtTable();
	}
	else if (ent1 == "variable" && attr1 == "varName") {
		list1 = PKBVariable::getVariables();
	}
	else if (ent1 == "read" && attr1 == "varName") {
		list1 = PKBRead::getAllReadVar();
	}
	else if (ent1 == "print" && attr1 == "varName") {
		list1 = PKBPrint::getAllPrintVar();
	}
	else if (ent1 == "constant" && attr1 == "value") {
		list1 = PKBConstant::getConstants();
	}
	else if (ent1 == "stmt" && attr1 =="stmt#") {
			list1 = PKBStmt::getStmts();
	}
	else if ((ent1 == "read" || ent1 == "print" || ent1 == "call" || ent1 == "while"
		|| ent1 == "if" || ent1 == "assign") && attr1 == "stmt#") {
		list1 = PKBStmt::getStmtsByType(ent1);
	}
	else {
		return resultTable;
	}

	if (ent2 == "procedure" && attr2 == "procName") {
		list2 = PKBProcedure::getProcedures();
	}
	else if (ent2 == "call" && attr2 == "procName") {
		list2 = PKBCall::getCallStmtTable();
	}
	else if (ent2 == "variable" && attr2 == "varName") {
		list2 = PKBVariable::getVariables();
	}
	else if (ent2 == "read" && attr2 == "varName") {
		list2 = PKBRead::getAllReadVar();
	}
	else if (ent2 == "print" && attr2 == "varName") {
		list2 = PKBPrint::getAllPrintVar();
	}
	else if (ent2 == "constant" && attr2 == "value") {
		list2 = PKBConstant::getConstants();
	}
	else if (ent2 == "stmt" && attr2 == "stmt#") {
		list2 = PKBStmt::getStmts();
	}
	else if ((ent2 == "read" || ent2 == "print" || ent2 == "call" || ent2 == "while"
		|| ent2 == "if" || ent2 == "assign") && attr2 == "stmt#") {
		list2 = PKBStmt::getStmtsByType(ent2);
	}
	else {
		return resultTable;
	}

	for (auto vectorIter1 : list1) {
		for (auto vectorIter2 : list2) {
			string ident1 = vectorIter1.front();
			string ident2 = vectorIter2.front();
			if ((ent1 == "read" && attr1 == "varName")  || (ent1 == "print" && attr1 == "varName") || (ent1 == "call" && attr1 == "procName")) {
				ident1 = vectorIter1.back();
			}
			if ((ent2 == "read" && attr2 == "varName")  || (ent2 == "print" && attr2 == "varName") || (ent2 == "call" && attr2 == "procName")) {
				ident2 = vectorIter2.back();
			}
			if (ident1 == ident2) {
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
	if (ent == "constant" && attr == "value") {
		list1 = PKBConstant::getConstants();
	}
	else {
		if (ent == "stmt" && attr == "stmt#") {
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
	
	if ((ent == "read" && attr == "varName" ) || (ent == "print" && attr == "varName") || (ent == "call" && attr == "procName")) {
		for (auto vectorIter1 : list1) {
			for (auto vectorIter2 : list2) {
				if (vectorIter1.back() == vectorIter2.front()) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter1.front());
					tuple.push_back(vectorIter2.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else {
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


