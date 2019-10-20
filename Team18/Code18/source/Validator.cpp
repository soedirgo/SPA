#include <algorithm>
#include <cctype>
#include <regex> // Now you have two problems ;)
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Validator.h"
#include "Query.h"

using namespace std;
namespace Validator {
    namespace {
        inline void trim(string& s, char c) {
            s.erase(s.begin(),
                    find_if_not(s.begin(),
                                s.end(),
                                [&c](int ch) {
                                    return ch == c;
                                }));
            s.erase(find_if_not(s.rbegin(),
                                s.rend(),
                                [&c](int ch) {
                                    return ch == c;
                                }).base(),
                    s.end());
        }

        inline void split(string s, string delim, vector<string>& results) {
            size_t pos = 0;
            string token;
            while ((pos = s.find(delim)) != string::npos) {
                token = s.substr(0, pos);
                results.push_back(token);
                s.erase(0, pos + delim.length());
            }
            trim(s, '_');
            results.push_back(s);
        }

        bool areDeclarationsValid(string& decl) {}

        bool isSelectValid(string& selectCl) {}

        bool isSuchThatValid(string& suchThatCl) {}

        bool isPatternValid(string& patternCl) {}

        bool isWithValid(string& withCl) {}

        bool areClausesValid(string& clauses) {}

        unordered_map<string, string> declarations;
    }

    bool isValid(string& input) {
        smatch wholeMatch;
        regex wholeRe("\\s*"
                      "(.*;)" // declaration
                      "\\s*"
                      "Select"
                      "\\s+"
                      "(BOOLEAN|[[:alpha:]][[:alnum:]]*|<.*>)" // select
                      "\\s+"
                      "(.*?)?" // clauses
                      "\\s*");
        if (!regex_match(input, wholeMatch, wholeRe))
            return false;

        if (!areDeclarationsValid(wholeMatch[1])
            || !isSelectValid(wholeMatch[2])
            || !areClausesValid(wholeMatch[3]))
            return false;

        return true;
    }
}
