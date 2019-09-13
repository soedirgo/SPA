#pragma once
#include <string>
#include <unordered_set>

namespace PKB {
	std::unordered_set<int> getAllStmt() {
        return { 1, 2, 3, 4, 5, 6, 7, 8 };
    }
    
	std::unordered_set<int> getAllAssignStmt() {
        return { 1, 2, 4, 5 };
    }
    
	std::unordered_set<int> getAllWhileStmt() {
        return { 6 };
    }
    
	std::unordered_set<int> getAllIfStmt() {
        return { 3 };
    }
    
	std::unordered_set<int> getAllPrintStmt() {
        return { 8 };
    }
    
	std::unordered_set<int> getAllReadStmt() {
        return { 7 };
    }
    
    std::unordered_set<std::string> getAllVar() {
        return { "x", "y", "z" };
    }
    
	std::unordered_set<std::string> getAllConstant() {
        return { "1", "0" };
    }
    
	std::unordered_set<std::string> getAllProc() {
        return { "main" };
    }
}
