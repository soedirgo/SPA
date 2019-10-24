#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include "PKBHash.h"

typedef std::string STMT_NO, PROG_LINE, VAR_NAME, PROC_NAME, CONST_VAL, STMT_TYPE, STMT_REF, ENT_TYPE, EXPR_SPEC, IDENT, ATTR;
typedef std::unordered_set <std::vector<std::string>> STMT_LIST,VAR_LIST, PROC_LIST, CONST_LIST, LINE_LIST, ENT_LIST;
typedef std::unordered_set <std::vector<std::string>> TABLE;