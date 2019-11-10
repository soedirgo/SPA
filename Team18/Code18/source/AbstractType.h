#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "PKBHash.h"

typedef std::string STMT_NO, PROG_LINE, VAR_NAME, PROC_NAME, CONST_VAL, STMT_TYPE, STMT_REF, ENT_TYPE, EXPR_SPEC, IDENT, ATTR;
typedef std::unordered_set <std::vector<std::string>> STMT_LIST,LIST_OF_VAR_NAME, LIST_OF_PROC_NAME, LIST_OF_CONS_VAL, LINE_LIST, ENT_LIST;
typedef std::unordered_set <std::vector<std::string>> TABLE;
typedef std::unordered_map <std::string, std::string> HASHMAP;