#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include "PKBHash.h"

//enum SYN { Read, Print, Assign, While, If, Call };
typedef std::string STMT_NO, PROG_LINE, VAR_NAME, PROC_NAME, CONST_VAL, STMT_TYPE, STMT_REF, ENT_REF;
typedef std::unordered_set <std::vector<std::string>, VectorHash> STMT_LIST,VAR_LIST, PROC_LIST, CONST_LIST, LINE_LIST;
typedef std::unordered_set <std::vector<std::string>, VectorHash> TABLE;