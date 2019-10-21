#include <algorithm>
#include <cctype>
#include <regex>
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

        unordered_map<string, string> synonymMap;

        bool areDeclarationsValid(string decl) {
            // ex: stmt s1 , s2 , s3 ; assign a ; variable a ;
            // whole declaration regex
            regex declsRe("("
                          "\\s*" // single decl starts here
                          "(stmt|read|print|call|while|if|assign"
                          "|variable|constant|prog_line|procedure)" // entity
                          "\\s+"
                          "(" // synonyms start here
                          "[[:alpha:]][[:alnum:]]*" // compulsory first synonym
                          "(" // additional synonyms start here
                          "\\s*"
                          ","
                          "\\s*"
                          "[[:alpha:]][[:alnum:]]*"
                          ")*" // additional synonyms end here
                          ")" // synonyms end here
                          "\\s*"
                          ";"
                          "\\s*" // single decl ends here
                          ")*");
            // check syntax
            if (!regex_match(decl, declsRe))
                return false;

            // single declaration regex
            regex declRe("(stmt|read|print|call|while|if|assign"
                         "|variable|constant|prog_line|procedure)" // entity
                         "\\s+"
                         "(" // synonyms start here
                         "[[:alpha:]][[:alnum:]]*" // compulsory first synonym
                         "(" // additional synonyms start here
                         "\\s*"
                         ","
                         "\\s*"
                         "[[:alpha:]][[:alnum:]]*"
                         ")*" // additional synonyms end here
                         ")" // synonyms end here
                         "\\s*"
                         ";");
            // single synonym regex
            regex synRe("[[:alpha:]][[:alnum:]]*");

            // map synonyms to entities
            auto declBegin = sregex_iterator(decl.begin(), decl.end(), declRe);
            auto reItEnd = sregex_iterator();

            for (sregex_iterator declIt = declBegin; declIt != reItEnd; ++declIt) {
                smatch sm = *declIt;
                string syns = sm[2];
                auto synBegin = sregex_iterator(syns.begin(), syns.end(), synRe);
                for (sregex_iterator synIt = synBegin; synIt != reItEnd; ++synIt) {
                    string syn = (*synIt).str();
                    if (synonymMap.count(syn))
                        return false;
                    synonymMap[syn] = sm[1];
                }
            }

            return true;
        }

        bool isSelectValid(string selectCl) {
            // ex: < s1 , s2 , s3 >
            // select synonyms regex
            regex selectRe("\\s*"
                           "(BOOLEAN|[[:alpha:]][[:alnum:]]*|" // non-tuple
                           "<" // start of tuple
                           "\\s*"
                           "[[:alpha:]][[:alnum:]]*" // compulsory first synonym
                           "("
                           "\\s*"
                           ","
                           "\\s*"
                           "[[:alpha:]][[:alnum:]]*" // other synonyms in tuple
                           ")*"
                           "\\s*"
                           ">" // end of tuple
                           ")"
                           "\\s*");
            smatch sm;
            if (!regex_match(selectCl, sm, selectRe))
                return false;

            // BOOLEAN or single synonym
            string syn = sm[0];
            if (syn == "BOOLEAN")
                return true;
            else if (syn.front() != '<') {
                if (synonymMap.count(syn))
                    return true;
                else
                    return false;
            }

            // single synonym regex
            regex synRe("[[:alpha:]][[:alnum:]]*");
            auto synBegin = sregex_iterator(syn.begin(), syn.end(), synRe);
            auto reItEnd = sregex_iterator();

            for (sregex_iterator synIt = synBegin; synIt != reItEnd; ++synIt) {
                string synStr = (*synIt).str();
                if (!synonymMap.count(synStr))
                    return false;
            }

            return true;
        }

        bool isSuchThatValid(string suchThatCl) {}

        bool isPatternValid(string patternCl) {}

        bool isWithValid(string withCl) {}

        bool areClausesValid(string clauses) {
            // ex: such that Uses ( "main" , x ) and Calls ( _ , _ )
            // pattern a ( v , " a + b " ) with s.stmt# = c.value
            regex clausesRe("(" // start of clause
                            "\\s*"
                            "such\\s+that" // start of such that
                            "[^\\)]+"
                            "\\)"
                            "(" // start of optional ``and''s
                            "\\s*"
                            "and"
                            "[^\\)]+"
                            "\\)"
                            ")*" // end of optional ``and''s
                            "|" // end of such that
                            "\\s*"
                            "pattern" // start of pattern
                            "[^\\)]+"
                            "\\)"
                            "(" // start of optional ``and''s
                            "\\s*"
                            "and"
                            "[^\\)]+"
                            "\\)"
                            ")*" // end of optional ``and''s
                            "|" // end of pattern
                            "\\s*"
                            "with" // start of with
                            "[^=]+"
                            "="
                            "\\s*"
                            "[^ ]+"
                            "(" // start of optional ``and''s
                            "\\s*"
                            "and"
                            "[^=]+"
                            "="
                            "\\s*"
                            "[^ ]+"
                            ")*" // end of optional ``and''s
                            ")*" // end of with and clause
                            "\\s*");
            if (!regex_match(clauses, clausesRe))
                return false;

            regex clauseRe("(" // start of clause
                           "(such\\s+that)" // start of such that
                           "[^\\)]+"
                           "\\)"
                           "(" // start of optional ``and''s
                           "\\s*"
                           "and"
                           "[^\\)]+"
                           "\\)"
                           ")*" // end of optional ``and''s
                           "|" // end of such that
                           "(pattern)" // start of pattern
                           "[^\\)]+"
                           "\\)"
                           "(" // start of optional ``and''s
                           "\\s*"
                           "and"
                           "[^\\)]+"
                           "\\)"
                           ")*" // end of optional ``and''s
                           "|" // end of pattern
                           "(with)" // start of with
                           "[^=]+"
                           "="
                           "\\s*"
                           "[^ ]+"
                           "(" // start of optional ``and''s
                           "\\s*"
                           "and"
                           "[^=]+"
                           "="
                           "\\s*"
                           "[^ ]+"
                           ")*" // end of optional ``and''s
                           ")"); // end of with and clause

            auto clauseBegin = sregex_iterator(clauses.begin(), clauses.end(), clauseRe);
            auto reItEnd = sregex_iterator();

            for (sregex_iterator clauseIt = clauseBegin; clauseIt != reItEnd; ++clauseIt) {
                
            }
        }
    }

    bool isValid(string& input) {
        smatch wholeMatch;
        regex wholeRe("\\s*"
                      "(.*;)?" // declaration
                      "\\s*"
                      "Select"
                      "\\s+"
                      "(BOOLEAN|[[:alpha:]][[:alnum:]]*|<.*>)" // select
                      "("
                      "\\s+"
                      "(.*?)" // clauses
                      ")?" // clauses may or may not exist
                      "\\s*");
        if (!regex_match(input, wholeMatch, wholeRe))
            return false;

        if (areDeclarationsValid(wholeMatch[1])
            && isSelectValid(wholeMatch[2])
            && areClausesValid(wholeMatch[4]))
            return true;
        else
            return false;
    }
}
