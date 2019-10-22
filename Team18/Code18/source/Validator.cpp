#include <regex>
#include <string>
#include <vector>
#include <unordered_map>
#include "Validator.h"

using namespace std;
namespace Validator {
    namespace {
        bool isExprSpecValid(string expr) {
            // if (expr.find("(") != string::npos) {
            //     int depth = 1;
            //     size_t pos = expr.find("(");
            //     size_t openPos = pos;
            //     while (depth) {
            //         size_t nextPos = expr.substr(pos + 1, string::npos).find_first_of("()");
            //         if (nextPos == string::npos) {
            //             return false;
            //         } else if (expr[nextPos] == '(') {
            //             ++depth;
            //             pos = nextPos;
            //         } else {
            //             --depth;
            //             pos = nextPos;
            //         }
            //     }
            //     size_t closePos = pos;
            //     return isPlusMinusValid(expr.substr(0, openPos))
            //         && isPlusMinusValid(expr.substr(openPos + 1, closePos))
            //         && isPlusMinusValid(expr.substr(closePos + 1, string::npos));
            // }

            // return isPlusMinusValid(expr);

            // validate brackets
            size_t pos = expr.find_first_of("()+-*/%");
            if (expr[pos] == ')') {
                return false;
            } else if (expr[pos] == '(') {
                int depth = 1;
                size_t nextPos = pos;
                while (depth) {
                    nextPos = expr.substr(nextPos + 1, string::npos).find_first_of("()");
                    if (nextPos == string::npos) {
                        return false;
                    } else if (expr[nextPos] == '(') {
                        ++depth;
                    } else {
                        --depth;
                    }
                }
                if (depth != 0)
                    return false;
            } else if (pos != string::npos) {
                return isExprSpecValid(expr.substr(0, pos))
                    && isExprSpecValid(expr.substr(pos + 1, string::npos));
            } else {
                return regex_match(expr, regex("\\s*"
                                               "([[:alpha:]][[:alnum:]]*"
                                               "|[[:digit:]]+)"
                                               "\\s*"));
            }
        }
    }

    bool isPatternValid(vector<string>& fields, unordered_map<string, string>& declMap) {
        regex synRe("[[:alpha:]][[:alnum:]]*");
        regex lhsRe("(_|[[:alpha:]][[:alnum:]]*|\"[[:alpha:]][[:alnum:]]*\")");
        regex rhsRe("(_|_\\s*,\\s*_|\"[^\"]+\"|_\"[^\"]+\"_)");

        string syn = fields[0];
        string lhs = fields[1];
        string rhs = fields[2];

        // match the damn things
        smatch synSm;
        if (!regex_match(syn, synSm, synRe))
            return false;

        smatch lhsSm;
        if (!regex_match(lhs, lhsSm, lhsRe))
            return false;

        smatch rhsSm;
        if (!regex_match(rhs, rhsSm, rhsRe))
            return false;

        // false if pattern synonym is undeclared
        if (!declMap.count(syn))
            return false;

        // false if pattern synonym is not assign/if/while
        if (declMap[syn] != "assign" && declMap[syn] != "if" && declMap[syn] != "while")
            return false;
		// false if pattern synonym is not if and 2nd and 3rd parameter is _
		if (declMap[syn] != "if" && regex_match(rhs, regex("_\\s*,\\s*_"))) {
            return false;
		}
        // false if pattern synonym is assign and rhs is expr_spec which is invalid
        if (declMap[syn] == "assign" && rhs != "_") {
            if (rhs.front() == '\"' && !isExprSpecValid(rhs.substr(1, rhs.length() - 2)))
                return false;
            else if (!isExprSpecValid(rhs.substr(2, rhs.length() - 4)))
                return false;
        }
		// false if pattern synonym is if and 2nd and 3rd parameter is not _
        if (declMap[syn] == "if" && !regex_match(rhs, regex("_\\s*,\\s*_"))) {
            return false;
		}
        // false if pattern synonym is while and 2nd parameter is not _
        if (declMap[syn] == "while" && rhs != "_")
            return false;
        // false if lhs is a synonym and is undeclared
        if (lhs != "_" && lhs.front() != '\"' && !declMap.count(lhs))
            return false;

		// false if lhs is syn that is not a variable
		if (lhs != "_" && lhs.front() != '\"' && declMap[lhs] != "variable")
			return false;

        return true;
    }
}
