#pragma once
#include <string>
#include <vector>
#include <unordered_set>

enum STMT_TYPE { Read, Print, Assign, While, If, Call };
typedef int STMT_NO, PROG_LINE;
typedef std::string VAR_NAME, PROC_NAME;
typedef std::unordered_set<int> STMT_LIST;
typedef std::unordered_set<std::string> VAR_LIST;
typedef std::unordered_set<std::string> PROC_LIST;
typedef std::unordered_set<std::string> CONST_LIST;