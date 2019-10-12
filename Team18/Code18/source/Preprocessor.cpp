#include <algorithm>
#include <cctype>
#include <regex> // Now you have two problems ;)
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "Preprocessor.h"
#include "Query.h"
using namespace std;

namespace Preprocessor {
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
        bool isSuchThatValid(string relRef, string lhs, string rhs, unordered_map<string, string>& synMap) {
            if (relRef == "Uses" || relRef == "Modifies") {
                if (lhs == "_")
                    return false;
                if (synMap.count(rhs)
                    && synMap[rhs] != "variable"
                    && synMap[rhs] != "constant")
                    return false;
            } else {
                if (synMap.count(lhs)
                    && (synMap[lhs] == "variable" || synMap[lhs] == "constant"))
                    return false;
            }
            if (synMap.count(lhs)
                && (synMap[lhs] == "variable" || synMap[lhs] == "constant"))
                return false;
            return true;
        }

        bool isPatternValid(string syn, string lhs, string rhs, unordered_map<string, string>& synMap) {
            if (!synMap.count(syn)
                || synMap[syn] != "assign")
                return false;
            if (synMap.count(lhs)
                && synMap[lhs] != "variable"
                && synMap[lhs] != "constant")
                return false;
            return true;
        }
    }

    bool isValid(string& input) {
        smatch selectClMatch;
        regex selectClRe("\\s*(.*;)"
                         "\\s*Select\\s+([[:alpha:]][[:alnum:]]*)"
                         "(\\s+(.*?))?\\s*");
        if (!regex_match(input, selectClMatch, selectClRe))
            return false;

        // smatch declarationsMatch;
        // regex declarationsRe("^(\\s*(stmt|read|print|while|if|assign|variable|constant|procedure)\\s+[[:alpha:]][[:alnum:]]*\\s*;)*$");
        // if (!regex_match(declarations, declarationsMatch, declarationsRe))
        //     return false;

        unordered_map<string, string> synonymMap;
        size_t pos;
        string declarations = selectClMatch[1];
        string declaration;
        smatch declarationMatch;
        regex declarationRe("\\s*(stmt|read|print|while|if|assign|variable|constant|procedure)"
                            "\\s+([[:alpha:]][[:alnum:]]*"
                            "(\\s*,\\s*[[:alpha:]][[:alnum:]]*)*"
                            ")\\s*");
        while ((pos = declarations.find(';')) != string::npos) {
            declaration = declarations.substr(0, pos);
            if (!regex_match(declaration, declarationMatch, declarationRe))
                return false;
            vector<string> synonyms;
            Preprocessor::split(declarationMatch[2], ",", synonyms);
            for (auto synonym : synonyms) {
                Preprocessor::trim(synonym, ' ');
                if (synonymMap.count(synonym))
                    return false;
                else
                    synonymMap[synonym] = declarationMatch[1];
            }
            declarations.erase(0, pos + 1);
        }
        if (!synonymMap.count(selectClMatch[2])) {
            return false;
        }
        // such that Uses(s, v)
        // such that Uses ( s , v )
        // such that .+ \\( ([[:alpha:]][[:alnum:]]*|_|"[[:digit:]]*" , [[:alpha:]][[:alnum:]]* \\)

        // pattern a(v, _"x"_)
        // pattern a ( v , _"x"_ )
        // pattern [[:alpha:]][[:alnum:]]* \\( [[:alpha:]][[:alnum:]]* , [[:w:]\\"]* \\)
        regex suchThatRe("\\s*such\\s+that\\s+"
                         "(Uses|Modifies|Follows|Follows\\*|Parent|Parent\\*)"
                         "\\s*\\(\\s*"
                         "([[:alpha:]][[:alnum:]]*|_|[[:digit:]]*)"
                         "\\s*,\\s*"
                         "([[:alpha:]][[:alnum:]]*|_|[[:digit:]]*|\\\"[[:alpha:]][[:alnum:]]*\\\")"
                         "\\s*\\)\\s*");
        regex patternRe("\\s*pattern\\s+"
                        "([[:alpha:]][[:alnum:]]*)"
                        "\\s*\\(\\s*"
                        "([[:alpha:]][[:alnum:]]*|_|\\\"[[:alpha:]][[:alnum:]]*\\\")"
                        "\\s*,\\s*"
                        "(_\\\"([[:alpha:]][[:alnum:]]*|[[:digit:]]*)\\\"_|_)"
                        "\\s*\\)\\s*");
        // regex clausesRe("(\\s*such\\s+that\\s+.+\\(\\s+([[:alpha:]][[:alnum:]]*|_|\\\"\\d+\\\")\\s+,\\s+[[:alpha:"
        //                 "|pattern"
        //                 "|with)");
        size_t suchThatPos;
        size_t patternPos;
        size_t currentClausePos;
        string clauses = selectClMatch[4];
        string clause;
        smatch clauseMatch;
        while (clauses.length() > 0) {
            // declaration = declarations.substr(0, pos);
            // if (!regex_match(declaration, declarationMatch, declarationRe))
            //     return false;
            // if (synonyms.count(declarationMatch[2]))
            //     return false;
            // else
            //     synonyms.insert(declarationMatch[2]);
            // declarations.erase(0, pos + 1);
            suchThatPos = clauses.find("such");
            patternPos = clauses.find("pattern");
            currentClausePos = min(suchThatPos, patternPos);
            if (currentClausePos == suchThatPos) {
                clause = clauses.substr(0, patternPos);
                if (!regex_match(clause, clauseMatch, suchThatRe))
                    return false;
                if (!isSuchThatValid(clauseMatch[1], clauseMatch[2], clauseMatch[3], synonymMap))
                    return false;
                clauses.erase(0, patternPos);
            } else if (currentClausePos == patternPos) {
                clause = clauses.substr(0, suchThatPos);
                if (!regex_match(clause, clauseMatch, patternRe))
                    return false;
                if (!isPatternValid(clauseMatch[1], clauseMatch[2], clauseMatch[3], synonymMap))
                    return false;
                clauses.erase(0, suchThatPos);
            } else {
                return false;
            }
        }
        return true;
    }

    //Query preprocess(string input) {
    //    return Query({}, "", {}, {});
    //}
}
