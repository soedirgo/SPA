#include <regex>
#include <string>
#include <vector>
#include <unordered_map>
#include "Validator.h"

using namespace std;
namespace Validator {
    namespace {
        bool isExprSpecValid(string expr);

        bool isTimesDivideModValid(string expr) {
            if () {
            }

            return isExprSpecValid() && isExprSpecValid();
        }

        bool isPlusMinusValid(string expr) {
            if () {
            }

            return isExprSpecValid() && isExprSpecValid();
        }

        bool isExprSpecValid(string expr) {
            if (expr.find("(") != string::npos) {
                int depth = 1;
                size_t pos = expr.find("(");
                while (pos != string::npos && depth) {
                    
                }
                
            }

            return isPlusMinusValid(expr);
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

        // false if lhs is a synonym and is undeclared
        if (lhs != "_" && lhs.front() != '\"' && !declMap.count(lhs))
            return false;

		// false if lhs is syn that is not a variable
		if (lhs != "_" && lhs.front() != '\"'
			&& declMap[lhs] != "variable")
			return false;

        // false if pattern synonym is not assign/if/while
        if (declMap[syn] != "assign" && declMap[syn] != "if" && declMap[syn] != "while")
            return false;

		// false if pattern synonym is not if and 2nd and 3rd parameter is _
		if (declMap[syn] != "if") {
			if (regex_match(rhs, regex("_\\s*,\\s*_")))
				return false;
		}
		// false if pattern synonym is if and 2nd and 3rd parameter is not _
        if (declMap[syn] == "if") {
			if (!regex_match(rhs, regex("_\\s*,\\s*_")))
			    return false;
		}
        // false if pattern synonym is while and 2nd parameter is not _
        if (declMap[syn] == "while" && fields[2] != "_")
            return false;

        return true;
    }
}
