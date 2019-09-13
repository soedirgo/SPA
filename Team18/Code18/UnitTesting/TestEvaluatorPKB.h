#pragma once
#include <string>
#include <unordered_set>

namespace PKB {
    std::unordered_set<std::string> getAllVar();
	std::unordered_set<std::string> getAllConstant();
	std::unordered_set<int> getAllStmt();
	std::unordered_set<std::string> getAllModifiesVar();
	std::unordered_set<std::string> getAllUsesVar();
	std::unordered_set<int> getAllModifiesStmt();
	std::unordered_set<int> getAllUsesStmt();
	std::unordered_set<int> getAllAssignStmt();
	std::unordered_set<int> getAllWhileStmt();
	std::unordered_set<int> getAllIfStmt();
	std::unordered_set<int> getAllPrintStmt();
	std::unordered_set<int> getAllReadStmt();
	std::unordered_set<std::string> getAllProc();
	std::unordered_set<int> getAllCallStmt();
}
