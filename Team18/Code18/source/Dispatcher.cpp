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
            return str.front() == '\"';
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
                  if (isdigit(lhs[1]))
                      if (isUnderscore(rhs))
                          return PKB::isUsesSIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isUsesSIdentIdent(trimQuotes(lhs),
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
                          return PKB::isUsesPIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isUsesPIdentIdent(trimQuotes(lhs),
                                                        trimQuotes(rhs));
          }},
         {"Modifies",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[1]))
                      if (isUnderscore(rhs))
                          return PKB::isModifiesSIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isModifiesSIdentIdent(trimQuotes(lhs),
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
                          return PKB::isModifiesPIdentAny(trimQuotes(lhs));
                      else
                          return PKB::isModifiesPIdentIdent(trimQuotes(lhs),
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
                      return PKB::isFollowsAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isFollowsIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isFollowsIdentIdent(trimQuotes(lhs),
                                                      trimQuotes(rhs));
          }},
         {"Follows*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isFollowsTAnyAny();
                  else
                      return PKB::isFollowsTAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isFollowsTIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isFollowsTIdentIdent(trimQuotes(lhs),
                                                       trimQuotes(rhs));
          }},
         {"Parent",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isParentAnyAny();
                  else
                      return PKB::isParentAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isParentIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isParentIdentIdent(trimQuotes(lhs),
                                                     trimQuotes(rhs));
          }},
         {"Parent*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isParentTAnyAny();
                  else
                      return PKB::isParentTAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isParentTIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isParentTIdentIdent(trimQuotes(lhs),
                                                      trimQuotes(rhs));
          }},
         {"Next",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isNextAnyAny();
                  else
                      return PKB::isNextAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isNextIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isNextIdentIdent(trimQuotes(lhs),
                                                   trimQuotes(rhs));
          }},
         {"Next*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isNextTAnyAny();
                  else
                      return PKB::isNextTAnyIdent(trimQuotes(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isNextTIdentAny(trimQuotes(lhs));
                  else
                      return PKB::isNextTIdentIdent(trimQuotes(lhs),
                                                    trimQuotes(rhs));
          }}};

        unordered_map<string, function<unordered_set<vector<string>>
                                       (string, string)>> suchThatTableApiMap =
        {{"Uses",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[1]))
                      return PKB::getUsesSIdentEnt(trimQuotes(lhs));
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
                  if (isdigit(lhs[1]))
                      return PKB::getModifiesSIdentEnt(trimQuotes(lhs));
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
                  return PKB::getFollowsIdentEnt(trimQuotes(lhs),
                                                 getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getFollowsEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getFollowsEntIdent(getEntity(lhs),
                                                     trimQuotes(rhs));
                  else
                      return PKB::getFollowsEntEnt(getEntity(lhs),
                                                   getEntity(rhs));
          }},
         {"Follows*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getFollowsTAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getFollowsTIdentEnt(trimQuotes(lhs),
                                                  getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getFollowsTEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getFollowsTEntIdent(getEntity(lhs),
                                                      trimQuotes(rhs));
                  else
                      return PKB::getFollowsTEntEnt(getEntity(lhs),
                                                    getEntity(rhs));
          }},
         {"Parent",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getParentAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getParentIdentEnt(trimQuotes(lhs),
                                                getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getParentEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getParentEntIdent(getEntity(lhs),
                                                    trimQuotes(rhs));
                  else
                      return PKB::getParentEntEnt(getEntity(lhs),
                                                  getEntity(rhs));
          }},
         {"Parent*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getParentTAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getParentTIdentEnt(trimQuotes(lhs),
                                                 getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getParentTEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getParentTEntIdent(getEntity(lhs),
                                                     trimQuotes(rhs));
                  else
                      return PKB::getParentTEntEnt(getEntity(lhs),
                                                   getEntity(rhs));
          }},
         {"Next",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getNextAnyEnt();
              else if (isIdentifier(lhs))
                  return PKB::getNextIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getNextEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getNextEntIdent(trimQuotes(rhs));
                  else
                      return PKB::getNextEntEnt();
          }},
         {"Next*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getNextTAnyEnt();
              else if (isIdentifier(lhs))
                  return PKB::getNextTIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getNextTEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getNextTEntIdent(trimQuotes(rhs));
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
            if (!isIdentifier(field) && field.front() != '_')
                synonyms[field] = synonyms.size();
        
        if (type == "such-that")
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
