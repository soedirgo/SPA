#include <functional>
#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Dispatcher.h"
#include "PKB.h"
#include "PKBHash.h"

using namespace std;
namespace Dispatcher {
    namespace {
        unordered_map<string, string> declarations;

        bool isUnderscore(string str) {
            return str == "_";
        }

        bool isIdentifier(string str) {
            return str.front() == '\"' || isdigit(str.front());
        }

        bool isFullPattern(string str) {
            //TODO: change this after shunting yard is implemented
            return str.front() != '\"';
        }

        string trimQuotes(string str) {
            return str.substr(1, str.size() - 2);
        }

        string getEntity(string& str) {
            return declarations[str];
        }

        unordered_map<string, function<bool(string, string)>> suchThatBoolApiMap =
        {{"Uses",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      if (isUnderscore(rhs))
                          return PKB::isUsesSIdentAny(lhs);
                      else
                          return PKB::isUsesSIdentIdent(lhs,
                                                        trimQuotes(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isUsesPIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isUsesPIdentIdent(trimQuotes(lhs),
                                                        trimQuotes(rhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::isUsesPIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isUsesPIdentIdent(trimQuotes(lhs),
                                                        trimQuotes(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isUsesSIdentAny(lhs);
                      else
                          return PKB::isUsesSIdentIdent(lhs,
                                                        trimQuotes(rhs));
          }},
         {"Modifies",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      if (isUnderscore(rhs))
                          return PKB::isModifiesSIdentAny(lhs);
                      else
                          return PKB::isModifiesSIdentIdent(lhs,
                                                            trimQuotes(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isModifiesPIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isModifiesPIdentIdent(trimQuotes(lhs),
                                                            trimQuotes(rhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::isModifiesPIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isModifiesPIdentIdent(trimQuotes(lhs),
                                                            trimQuotes(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isModifiesSIdentAny(lhs);
                      else
                          return PKB::isModifiesSIdentIdent(lhs,
                                                            trimQuotes(rhs));
          }},
         {"Calls",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isCallsAnyAny();
                  else
                      return PKB::isCallsAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isCallsIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isCallsIdentIdent(trimQuotes(lhs),
                                                    trimQuotes(rhs));
          }},
         {"Follows",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isFollowsAnyAny();
                  else
                      return PKB::isFollowsAnyIdent(rhs);
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isFollowsIdentAny(lhs);
                  else
                      return PKB::isFollowsIdentIdent(lhs,
                                                      rhs);
          }},
         {"Follows*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isFollowsTAnyAny();
                  else
                      return PKB::isFollowsTAnyIdent(rhs);
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isFollowsTIdentAny(lhs);
                  else
                      return PKB::isFollowsTIdentIdent(lhs,
                                                       rhs);
          }},
         {"Parent",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isParentAnyAny();
                  else
                      return PKB::isParentAnyIdent(rhs);
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isParentIdentAny(lhs);
                  else
                      return PKB::isParentIdentIdent(lhs,
                                                     rhs);
          }},
         {"Parent*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isParentTAnyAny();
                  else
                      return PKB::isParentTAnyIdent(rhs);
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isParentTIdentAny(lhs);
                  else
                      return PKB::isParentTIdentIdent(lhs,
                                                      rhs);
          }},
         {"Next",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isNextAnyAny();
                  else
                      return PKB::isNextAnyIdent(rhs);
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isNextIdentAny(lhs);
                  else
                      return PKB::isNextIdentIdent(lhs,
                                                   rhs);
          }},
         {"Next*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isNextTAnyAny();
                  else
                      return PKB::isNextTAnyIdent(rhs);
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isNextTIdentAny(lhs);
                  else
                      return PKB::isNextTIdentIdent(lhs,
                                                    rhs);
          }}};

        unordered_map<string, function<unordered_set<vector<string>>
                                       (string, string)>> suchThatTableApiMap =
        {{"Uses",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      return PKB::getUsesSIdentEnt(lhs);
                  else
                      return PKB::getUsesPIdentEnt(trimQuotes(lhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::getUsesPEntAny();
                      else if (isIdentifier(rhs))
                          return PKB::getUsesPEntIdent(trimQuotes(rhs));
                      else
                          return PKB::getUsesPEntEnt();
                  else
                      if (isUnderscore(rhs))
                          return PKB::getUsesSEntAny(getEntity(lhs));
                      else if (isIdentifier(rhs))
                          return PKB::getUsesSEntIdent(getEntity(lhs),
                                                       trimQuotes(rhs));
                      else
                          return PKB::getUsesSEntEnt(getEntity(lhs));
          }},
         {"Modifies",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      return PKB::getModifiesSIdentEnt(lhs);
                  else
                      return PKB::getModifiesPIdentEnt(trimQuotes(lhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::getModifiesPEntAny();
                      else if (isIdentifier(rhs))
                          return PKB::getModifiesPEntIdent(trimQuotes(rhs));
                      else
                          return PKB::getModifiesPEntEnt();
                  else
                      if (isUnderscore(rhs))
                          return PKB::getModifiesSEntAny(getEntity(lhs));
                      else if (isIdentifier(rhs))
                          return PKB::getModifiesSEntIdent(getEntity(lhs),
                                                           trimQuotes(rhs));
                      else
                          return PKB::getModifiesSEntEnt(getEntity(lhs));
          }},
         {"Calls",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getCallsAnyEnt();
              else if (isIdentifier(lhs))
                  return PKB::getCallsIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getCallsEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getCallsEntIdent(trimQuotes(rhs));
                  else
                      return PKB::getCallsEntEnt();
          }},
         {"Follows",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getFollowsAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getFollowsIdentEnt(lhs,
                                                 getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getFollowsEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getFollowsEntIdent(getEntity(lhs),
                                                     rhs);
                  else if (lhs == rhs)
                      return unordered_set<vector<string>>();
                  else
                      return PKB::getFollowsEntEnt(getEntity(lhs),
                                                   getEntity(rhs));
          }},
         {"Follows*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getFollowsTAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getFollowsTIdentEnt(lhs,
                                                  getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getFollowsTEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getFollowsTEntIdent(getEntity(lhs),
                                                      rhs);
                  else if (lhs == rhs)
                      return unordered_set<vector<string>>();
                  else
                      return PKB::getFollowsTEntEnt(getEntity(lhs),
                                                    getEntity(rhs));
          }},
         {"Parent",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getParentAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getParentIdentEnt(lhs,
                                                getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getParentEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getParentEntIdent(getEntity(lhs),
                                                    rhs);
                  else if (lhs == rhs)
                      return unordered_set<vector<string>>();
                  else
                      return PKB::getParentEntEnt(getEntity(lhs),
                                                  getEntity(rhs));
          }},
         {"Parent*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getParentTAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getParentTIdentEnt(lhs,
                                                 getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getParentTEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getParentTEntIdent(getEntity(lhs),
                                                     rhs);
                  else if (lhs == rhs)
                      return unordered_set<vector<string>>();
                  else
                      return PKB::getParentTEntEnt(getEntity(lhs),
                                                   getEntity(rhs));
          }},
         {"Next",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getNextAnyEnt();
              else if (isIdentifier(lhs))
                  return PKB::getNextIdentEnt(lhs);
              else
                  if (isUnderscore(rhs))
                      return PKB::getNextEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getNextEntIdent(rhs);
                  else if (lhs == rhs)
                      return unordered_set<vector<string>>();
                  else
                      return PKB::getNextEntEnt();
          }},
         {"Next*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getNextTAnyEnt();
              else if (isIdentifier(lhs))
                  return PKB::getNextTIdentEnt(lhs);
              else
                  if (isUnderscore(rhs))
                      return PKB::getNextTEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getNextTEntIdent(rhs);
                  else if (lhs == rhs)
                      return PKB::getNextTSelf();
                  else
                      return PKB::getNextTEntEnt();
          }}};

        unordered_map<string, function<unordered_set<vector<string>>
                                       (string, string)>> patternApiMap =
        {{"assign",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::getPatternAssignAnyAny();
                  else if (isFullPattern(rhs))
                      return PKB::getPatternAssignAnyFull(rhs);
                  else
                      return PKB::getPatternAssignAnyPartial(rhs);
              else if (isIdentifier(lhs))
                  if (isUnderscore(rhs))
                      return PKB::getPatternAssignIdentAny(trimQuotes(lhs));
                  else if (isFullPattern(rhs))
                      return PKB::getPatternAssignIdentFull(trimQuotes(lhs),
                                                            rhs);
                  else
                      return PKB::getPatternAssignIdentPartial(trimQuotes(lhs),
                                                               rhs);
              else
                  if (isUnderscore(rhs))
                      return PKB::getPatternAssignEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getPatternAssignEntFull(rhs);
                  else
                      return PKB::getPatternAssignEntPartial(rhs);
          }},
         {"if",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getPatternIfAny();
              else if (isIdentifier(lhs))
                  return PKB::getPatternIfIdent(trimQuotes(lhs));
              else
                  return PKB::getPatternIfEnt();
          }},
         {"while",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getPatternIfAny();
              else if (isIdentifier(lhs))
                  return PKB::getPatternIfIdent(trimQuotes(lhs));
              else
                  return PKB::getPatternIfEnt();
          }}};
    }

    void dispatch(Clause& clause,
                  unordered_map<string, string>& decl,
                  bool& resultExists,
                  unordered_map<string, int>& synonyms,
                  unordered_set<vector<string>>& results) {
        string type = clause.getType();
        vector<string> fields = clause.getFields();
        declarations = decl;

        for (const auto& field : fields)
            if (type == "such that" && field == fields[0])
                continue;
            else if (!isIdentifier(field) && field.front() != '_')
                synonyms[field] = synonyms.size();
        
        if (type == "such that")
            if ((isUnderscore(fields[1]) || isIdentifier(fields[1]))
                && (isUnderscore(fields[2]) || isIdentifier(fields[2])))
                resultExists = suchThatBoolApiMap[fields[0]](fields[1], fields[2]);
            else {
                results = suchThatTableApiMap[fields[0]](fields[1], fields[2]);
                resultExists = results.size();
            }
        else if (type == "pattern") {
            results = patternApiMap[getEntity(fields[0])](fields[1], fields[2]);
            resultExists = results.size();
        }
    }
}
