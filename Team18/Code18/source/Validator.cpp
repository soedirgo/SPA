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
        // inline void trim(string& s, char c) {
        //     s.erase(s.begin(),
        //             find_if_not(s.begin(),
        //                         s.end(),
        //                         [&c](int ch) {
        //                             return ch == c;
        //                         }));
        //     s.erase(find_if_not(s.rbegin(),
        //                         s.rend(),
        //                         [&c](int ch) {
        //                             return ch == c;
        //                         }).base(),
        //             s.end());
        // }

        // inline void split(string s, string delim, vector<string>& results) {
        //     size_t pos = 0;
        //     string token;
        //     while ((pos = s.find(delim)) != string::npos) {
        //         token = s.substr(0, pos);
        //         results.push_back(token);
        //         s.erase(0, pos + delim.length());
        //     }
        //     trim(s, '_');
        //     results.push_back(s);
        // }

        // unordered_map<string, string> synonymMap;

        // inline bool isSynonym(string& s) {
        //     return s != "_" && s.front() != '\"';
        // }

        // bool areDeclarationsValid(string decl) {
        //     // ex: stmt s1 , s2 , s3 ; assign a ; variable a ;
        //     // whole declaration regex
        //     regex declsRe("("
        //                   "\\s*" // single decl starts here
        //                   "(stmt|read|print|call|while|if|assign"
        //                   "|variable|constant|prog_line|procedure)" // entity
        //                   "\\s+"
        //                   "(" // synonyms start here
        //                   "[[:alpha:]][[:alnum:]]*" // compulsory first synonym
        //                   "(" // additional synonyms start here
        //                   "\\s*"
        //                   ","
        //                   "\\s*"
        //                   "[[:alpha:]][[:alnum:]]*"
        //                   ")*" // additional synonyms end here
        //                   ")" // synonyms end here
        //                   "\\s*"
        //                   ";"
        //                   "\\s*" // single decl ends here
        //                   ")*");
        //     // check syntax
        //     if (!regex_match(decl, declsRe))
        //         return false;

        //     // single declaration regex
        //     regex declRe("(stmt|read|print|call|while|if|assign"
        //                  "|variable|constant|prog_line|procedure)" // entity
        //                  "\\s+"
        //                  "(" // synonyms start here
        //                  "[[:alpha:]][[:alnum:]]*" // compulsory first synonym
        //                  "(" // additional synonyms start here
        //                  "\\s*"
        //                  ","
        //                  "\\s*"
        //                  "[[:alpha:]][[:alnum:]]*"
        //                  ")*" // additional synonyms end here
        //                  ")" // synonyms end here
        //                  "\\s*"
        //                  ";");
        //     // single synonym regex
        //     regex synRe("[[:alpha:]][[:alnum:]]*");

        //     // map synonyms to entities
        //     auto declBegin = sregex_iterator(decl.begin(), decl.end(), declRe);
        //     auto reItEnd = sregex_iterator();

        //     for (sregex_iterator declIt = declBegin; declIt != reItEnd; ++declIt) {
        //         smatch sm = *declIt;
        //         string syns = sm[2];
        //         auto synBegin = sregex_iterator(syns.begin(), syns.end(), synRe);
        //         for (sregex_iterator synIt = synBegin; synIt != reItEnd; ++synIt) {
        //             string syn = (*synIt).str();
        //             if (synonymMap.count(syn))
        //                 return false;
        //             synonymMap[syn] = sm[1];
        //         }
        //     }

        //     return true;
        // }

        // bool isSelectValid(string selectCl) {
        //     // ex: < s1 , s2 , s3 >
        //     // select synonyms regex
        //     regex selectRe("\\s*"
        //                    "(BOOLEAN|[[:alpha:]][[:alnum:]]*|" // non-tuple
        //                    "<" // start of tuple
        //                    "\\s*"
        //                    "[[:alpha:]][[:alnum:]]*" // compulsory first synonym
        //                    "("
        //                    "\\s*"
        //                    ","
        //                    "\\s*"
        //                    "[[:alpha:]][[:alnum:]]*" // other synonyms in tuple
        //                    ")*"
        //                    "\\s*"
        //                    ">" // end of tuple
        //                    ")"
        //                    "\\s*");
        //     smatch sm;
        //     if (!regex_match(selectCl, sm, selectRe))
        //         return false;

        //     // BOOLEAN or single synonym
        //     string syn = sm[0];
        //     if (syn == "BOOLEAN")
        //         return true;
        //     else if (syn.front() != '<') {
        //         if (synonymMap.count(syn))
        //             return true;
        //         else
        //             return false;
        //     }

        //     // single synonym regex
        //     regex synRe("[[:alpha:]][[:alnum:]]*");
        //     auto synBegin = sregex_iterator(syn.begin(), syn.end(), synRe);
        //     auto reItEnd = sregex_iterator();

        //     for (sregex_iterator synIt = synBegin; synIt != reItEnd; ++synIt) {
        //         string synStr = (*synIt).str();
        //         if (!synonymMap.count(synStr))
        //             return false;
        //     }

        //     return true;
        // }

        // bool isSuchThatValid(string suchThatCl) {
        //     // ex: such that Uses ( "main" , x ) and Calls ( _ , _ )
        //     // such that regex
        //     regex suchThatRe("(Uses|Modifies|Calls|Calls\\*|Follows|Follows\\*"
        //                      "|Parent|Parent\\*|Next|Next\\*|Affects|Affects\\*)" // rel
        //                      "\\s*"
        //                      "\\("
        //                      "\\s*"
        //                      "(_|[[:alpha:]][[:alnum:]]*|[[:digit:]]*"
        //                      "|\"[[:alpha:]][[:alnum:]]\")" // lhs
        //                      "\\s*"
        //                      ","
        //                      "\\s*"
        //                      "(_|[[:alpha:]][[:alnum:]]*|[[:digit:]]*"
        //                      "|\"[[:alpha:]][[:alnum:]]*\")" // rhs
        //                      "\\s*"
        //                      "\\)");

        //     auto suchThatBegin = sregex_iterator(suchThatCl.begin(), suchThatCl.end(), suchThatRe);
        //     auto reItEnd = sregex_iterator();

        //     for (sregex_iterator suchThatIt = suchThatBegin; suchThatIt != reItEnd; ++suchThatIt) {
        //         smatch sm = *suchThatIt;
        //         string rel = sm[1];
        //         string lhs = sm[2];
        //         string rhs = sm[3];
        //         // every synonym must be declared
        //         if (isSynonym(lhs))
        //             if (!synonymMap.count(lhs))
        //                 return false;
        //         if (isSynonym(rhs))
        //             if (!synonymMap.count(rhs))
        //                 return false;
        //         // lhs can't be _
        //         // rhs must be varRef
        //         if (rel == "Uses" || rel == "Modifies") {
        //             if (lhs == "_"
        //                 || isSynonym(rhs) && synonymMap[rhs] != "variable")
        //                 return false;
        //         }
        //         // both must be procRef
        //         if (rel == "Calls" || rel == "Calls*") {
        //             if (isSynonym(lhs) && synonymMap[lhs] != "procedure"
        //                 || isSynonym(rhs) && synonymMap[rhs] != "procedure")
        //                 return false;
        //         }
        //         // variable is only used on Uses and Modifies
        //         if (isSynonym(lhs) && synonymMap[lhs] == "variable"
        //             || isSynonym(rhs) && synonymMap[rhs] == "variable")
        //             if (rel != "Uses" && rel != "Modifies")
        //                 return false;
        //         // can't have constant synonym
        //         if (isSynonym(lhs) && synonymMap[lhs] == "constant"
        //             || isSynonym(rhs) && synonymMap[rhs] == "constant")
        //             return false;
        //         // procedure is only used on Calls
        //         if (isSynonym(lhs) && synonymMap[lhs] == "procedure"
        //             || isSynonym(rhs) && synonymMap[rhs] == "procedure")
        //             if (rel != "Calls" && rel != "Calls*")
        //                 return false;
        //         // numbers are only used in place of stmtRef
        //         if (isdigit(lhs.front()))
        //             if (rel == "Calls" || rel == "Calls*")
        //                 return false;
        //         if (isdigit(rhs.front()))
        //             if (rel == "Uses" || rel == "Modifies" || rel == "Calls" || rel == "Calls*")
        //                 return false;
        //         // idents are only used in place of varRef, procRef
        //         if (lhs.front() == '\"')
        //             if (rel != "Uses" && rel != "Modifies" && rel != "Calls" && rel != "Calls*")
        //                 return false;
        //         if (rhs.front() == '\"')
        //             if (rel != "Uses" && rel != "Modifies" && rel != "Calls" && rel != "Calls*")
        //                 return false;
        //     }

        //     return true;
        // }

        // bool isWithValid(string withCl) {
        //     // ex: with s.stmt# = c.value and n = 10
        //     // with regex
        //     regex withRe("[[:digit:]]|\"[[:alpha:]][[:alnum:]]*\"|[[:alpha:]][[:alnum:]]*"
        //                  "|[[:alpha:]][[:alnum:]]*\\.(stmt#|varName|procName|value)"
        //                  "\\s*"
        //                  "="
        //                  "\\s*"
        //                  "[[:digit:]]|\"[[:alpha:]][[:alnum:]]*\"|[[:alpha:]][[:alnum:]]*"
        //                  "|[[:alpha:]][[:alnum:]]*\\.(stmt#|varName|procName|value)");

        //     auto withBegin = sregex_iterator(withCl.begin(), withCl.end(), withRe);
        //     auto reItEnd = sregex_iterator();

        //     for (sregex_iterator withIt = withBegin; withIt != reItEnd; ++withIt) {
        //         smatch sm = *withIt;
        //         string lhs = sm[1];
        //         string rhs = sm[2];
        //         // synonym must be declared
        //         // attributes must match
        //         // attributes must be of the same type
        //     }

        //     return true;
        // }

        // bool areClausesValid(string clauses) {
        //     // ex: such that Uses ( "main" , x ) and Calls ( _ , _ )
        //     // pattern a ( v , " a + b " ) with s.stmt# = c.value
        //     // whole clauses regex
        //     regex clausesRe(
        //         "(" // start of clause
        //         "\\s*"
        //         "such\\s+that" // start of such that
        //         "\\s+"
        //         "(Uses|Modifies|Calls|Calls\\*|Follows|Follows\\*"
        //         "|Parent|Parent\\*|Next|Next\\*|Affects|Affects\\*)" // rel
        //         "\\s*"
        //         "\\("
        //         "\\s*"
        //         "(_|[[:alpha:]][[:alnum:]]*|[[:digit:]]*"
        //         "|\"[[:alpha:]][[:alnum:]]\")" // lhs
        //         "\\s*"
        //         ","
        //         "\\s*"
        //         "(_|[[:alpha:]][[:alnum:]]*|[[:digit:]]*"
        //         "|\"[[:alpha:]][[:alnum:]]\")" // rhs
        //         "\\s*"
        //         "\\)"
        //         "(" // start of optional ``and''s
        //         "\\s*"
        //         "and"
        //         "\\s+"
        //         "(Uses|Modifies|Calls|Calls\\*|Follows|Follows\\*"
        //         "|Parent|Parent\\*|Next|Next\\*|Affects|Affects\\*)" // rel
        //         "\\s*"
        //         "\\("
        //         "\\s*"
        //         "(_|[[:alpha:]][[:alnum:]]*|[[:digit:]]*"
        //         "|\"[[:alpha:]][[:alnum:]]\")" // lhs
        //         "\\s*"
        //         ","
        //         "\\s*"
        //         "(_|[[:alpha:]][[:alnum:]]*|[[:digit:]]*"
        //         "|\"[[:alpha:]][[:alnum:]]\")" // lhs
        //         "\\s*"
        //         "\\)"
        //         ")*" // end of optional ``and''s
        //         "|" // end of such that
        //         "\\s*"
        //         "pattern" // start of pattern
        //         "\\s+"
        //         "[[:alpha:]][[:alnum:]]*" // synonym
        //         "\\s*"
        //         "\\("
        //         "\\s*"
        //         "_|[[:alpha:]][[:alnum:]]*|\"[[:alpha:]][[:alnum:]]*\"" // lhs
        //         "\\s*"
        //         ","
        //         "\\s*"
        //         "_|[[:alpha:]][[:alnum:]]*|_\\s*,\\s*_" // rhs
        //         "\\s*"
        //         "\\)"
        //         "(" // start of optional ``and''s
        //         "\\s*"
        //         "and"
        //         "\\s+"
        //         "[[:alpha:]][[:alnum:]]*" // synonym
        //         "\\s*"
        //         "\\("
        //         "\\s*"
        //         "_|[[:alpha:]][[:alnum:]]*|\"[[:alpha:]][[:alnum:]]*\"" // lhs
        //         "\\s*"
        //         ","
        //         "\\s*"
        //         "_|[[:alpha:]][[:alnum:]]*|_\\s*,\\s*_" // rhs
        //         "\\s*"
        //         "\\)"
        //         ")*" // end of optional ``and''s
        //         "|" // end of pattern
        //         "\\s*"
        //         "with" // start of with
        //         "\\s+"
        //         "[[:digit:]]|\"[[:alpha:]][[:alnum:]]*\"|[[:alpha:]][[:alnum:]]*"
        //         "|[[:alpha:]][[:alnum:]]*\\.(stmt#|varName|procName|value)"
        //         "\\s*"
        //         "="
        //         "\\s*"
        //         "[[:digit:]]|\"[[:alpha:]][[:alnum:]]*\"|[[:alpha:]][[:alnum:]]*"
        //         "|[[:alpha:]][[:alnum:]]*\\.(stmt#|varName|procName|value)"
        //         "(" // start of optional ``and''s
        //         "\\s+"
        //         "and"
        //         "\\s+"
        //         "[[:digit:]]|\"[[:alpha:]][[:alnum:]]*\"|[[:alpha:]][[:alnum:]]*"
        //         "|[[:alpha:]][[:alnum:]]*\\.(stmt#|varName|procName|value)"
        //         "\\s*"
        //         "="
        //         "\\s*"
        //         "[[:digit:]]|\"[[:alpha:]][[:alnum:]]*\"|[[:alpha:]][[:alnum:]]*"
        //         "|[[:alpha:]][[:alnum:]]*\\.(stmt#|varName|procName|value)"
        //         ")*" // end of optional ``and''s
        //         ")*" // end of with and clause
        //         "\\s*");
        //     if (!regex_match(clauses, clausesRe))
        //         return false;

        //     regex clauseRe("(" // start of clause
        //                    "(such\\s+that)" // start of such that
        //                    "[^\\)]+"
        //                    "\\)"
        //                    "(" // start of optional ``and''s
        //                    "\\s*"
        //                    "and"
        //                    "[^\\)]+"
        //                    "\\)"
        //                    ")*" // end of optional ``and''s
        //                    "|" // end of such that
        //                    "(pattern)" // start of pattern
        //                    "[^\\)]+"
        //                    "\\)"
        //                    "(" // start of optional ``and''s
        //                    "\\s*"
        //                    "and"
        //                    "[^\\)]+"
        //                    "\\)"
        //                    ")*" // end of optional ``and''s
        //                    "|" // end of pattern
        //                    "(with)" // start of with
        //                    "[^=]+"
        //                    "="
        //                    "\\s*"
        //                    "[^ ]+"
        //                    "(" // start of optional ``and''s
        //                    "\\s*"
        //                    "and"
        //                    "[^=]+"
        //                    "="
        //                    "\\s*"
        //                    "[^ ]+"
        //                    ")*" // end of optional ``and''s
        //                    ")"); // end of with and clause

        //     auto clauseBegin = sregex_iterator(clauses.begin(), clauses.end(), clauseRe);
        //     auto reItEnd = sregex_iterator();

        //     for (sregex_iterator clauseIt = clauseBegin; clauseIt != reItEnd; ++clauseIt) {
        //         smatch sm = *clauseIt;
        //         if (sm[2].length() && !isSuchThatValid(sm[1].str()))
        //             return false;
        //         else if (sm[4].length() && !isPatternValid(sm[1].str()))
        //             return false;
        //         else if (sm[6].length() && !isWithValid(sm[1].str()))
        //             return false;
        //         else
        //             return false;
        //     }

        //     return true;
        // }
    }

    // bool isValid(string& input) {
    //     smatch wholeMatch;
    //     regex wholeRe("\\s*"
    //                   "(.*;)?" // declaration
    //                   "\\s*"
    //                   "Select"
    //                   "\\s+"
    //                   "(BOOLEAN|[[:alpha:]][[:alnum:]]*|<.*>)" // select
    //                   "("
    //                   "\\s+"
    //                   "(.*?)" // clauses
    //                   ")?" // clauses may or may not exist
    //                   "\\s*");
    //     if (!regex_match(input, wholeMatch, wholeRe))
    //         return false;

    //     if (areDeclarationsValid(wholeMatch[1])
    //         && isSelectValid(wholeMatch[2])
    //         && areClausesValid(wholeMatch[4]))
    //         return true;
    //     else
    //         return false;
    // }

    bool isPatternValid(vector<string>& fields, unordered_map<string, string>& declMap) {
        // ex: pattern a ( _ , " a + b " ) and w ( v , _ )
        // pattern regex
        // regex patternRe("([[:alpha:]][[:alnum:]]*)" // synonym
        //                 "\\s*"
        //                 "\\("
        //                 "\\s*"
        //                 "(_|[[:alpha:]][[:alnum:]]*"
        //                 "|\"[[:alpha:]][[:alnum:]]\")" // lhs
        //                 "\\s*"
        //                 ","
        //                 "\\s*"
        //                 "(_|_\\s*,\\s*_|\"[^\"]+\")" // rhs
        //                 "\\s*"
        //                 "\\)");

        // auto patternBegin = sregex_iterator(patternCl.begin(), patternCl.end(), patternRe);
        // auto reItEnd = sregex_iterator();

        // for (sregex_iterator patternIt = patternBegin; patternIt != reItEnd; ++patternIt) {
        //     smatch sm = *patternIt;
        //     string syn = sm[1];
        //     string lhs = sm[2];
        //     string rhs = sm[3];
        //     // synonym must be declared
        //     if (!synonymMap.count(syn))
        //         return false;
        //     if (isSynonym(lhs))
        //         if (!synonymMap.count(rhs))
        //             return false;
        //     // synonym must be assign/if/while
        //     if (synonymMap[syn] == "if") {
        //         if (rhs == "_" || rhs.front() == '\"')
        //             return false;
        //     } else if (synonymMap[syn] == "while") {
        //         if (rhs != "_")
        //             return false;
        //     } else {
        //         //TODO: check expr_spec
        //     }
        // }

        regex synRe("[[:alpha:]][[:alnum:]]*");
        regex lhsRe("(_|[[:alpha:]][[:alnum:]]*|\"[[:alpha:]][[:alnum:]]*\")");
        regex rhsRe("(_|\"[^\"]+\")");

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

        // false if pattern synonym is not assign/if/while
        if (declMap[syn] != "assign" && declMap[syn] != "if" && declMap[syn] != "while")
            return false;

        // false if pattern synonym is if and 2nd and 3rd parameter is not _
        if (declMap[syn] == "if" && (fields[2] != "_" || fields[3] != "_"))
            return false;
        // false if pattern synonym is while and 2nd parameter is not _
        if (declMap[syn] == "while" && fields[2] != "_")
            return false;

        return true;
    }
}
