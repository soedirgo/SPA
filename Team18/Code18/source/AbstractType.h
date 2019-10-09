#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include "PKBHash.h"

//enum STMT_TYPE { Read, Print, Assign, While, If, Call };
typedef std::string STMT_NO, PROG_LINE, VAR_NAME, PROC_NAME, CONST_VAL, STMT_TYPE;
typedef std::unordered_set <std::vector<std::string>, VectorSingleStringHash> STMT_LIST,VAR_LIST, PROC_LIST, CONST_LIST, LINE_LIST;
typedef std::unordered_set <std::vector<std::string>, VectorDoubleStringHash> TABLE;