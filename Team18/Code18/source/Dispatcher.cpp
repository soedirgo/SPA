#include <functional>
#include <string>
#include <unordered_map>
#include "Dispatcher.h"
#include "PKB.h"
#include "PKBHash.h"

using namespace std;
namespace Dispatcher {
    namespace {
        unordered_map<string, string> declarations;

        bool isUnderscore(string& str) {
            return str == "_";
        }

        bool isIdentifier(string& str) {
            return str.front() == '\"';
        }

        string trimQuotes(string str) {
            return str.substr(1, str.size() - 2);
        }

        string getEntity(string& str) {
            return declarations[str];
        }

        unordered_map<string, function<bool(string, string)>> boolApiMap =
        {{"UsesS",
          [](string lhs, string rhs) {
              if (isUnderscore(rhs))
                  return PKB::isUsesSIdentAny(trimQuotes(lhs));
              else
                  return PKB::isUsesSIdentIdent(trimQuotes(lhs),
                                                trimQuotes(rhs));
          }},
         {"UsesP",
          [](string lhs, string rhs) {
              if (isUnderscore(rhs))
                  return PKB::isUsesPIdentAny(trimQuotes(lhs));
              else
                  return PKB::isUsesPIdentIdent(trimQuotes(lhs),
                                                trimQuotes(rhs));
          }},
         {"ModifiesS",
          [](string lhs, string rhs) {
              if (isUnderscore(rhs))
                  return PKB::isModifiesSIdentAny(trimQuotes(lhs));
              else
                  return PKB::isModifiesSIdentIdent(trimQuotes(lhs),
                                                    trimQuotes(rhs));
          }},
         {"ModifiesP",
          [](string lhs, string rhs) {
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
                                       (string, string)>> tableApiMap =
        {{"UsesS",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  return PKB::getUsesSIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getUsesSEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getUsesSEntIdent(getEntity(lhs),
                                                   trimQuotes(rhs));
                  else
                      return PKB::getUsesSEntEnt(getEntity(lhs));
          }},
         {"UsesP",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  return PKB::getUsesPIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getUsesPEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getUsesPEntIdent(trimQuotes(rhs));
                  else
                      return PKB::getUsesPEntEnt();
          }},
         {"ModifiesS",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  return PKB::getModifiesSIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getModifiesSEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getModifiesSEntIdent(getEntity(lhs),
                                                   trimQuotes(rhs));
                  else
                      return PKB::getModifiesSEntEnt(getEntity(lhs));
          }},
         {"ModifiesP",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  return PKB::getModifiesPIdentEnt(trimQuotes(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getModifiesPEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getModifiesPEntIdent(trimQuotes(rhs));
                  else
                      return PKB::getModifiesPEntEnt();
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
    }

    void dispatch(string rel,
                  string lhs,
                  string rhs,
                  unordered_map<string, string>& decl,
                  bool& resultExists,
                  unordered_set<vector<string>>& results) {
        declarations = decl;
        if ((isUnderscore(lhs) || isIdentifier(lhs))
            && (isUnderscore(rhs) || isIdentifier(rhs)))
            resultExists = boolApiMap[rel](lhs, rhs);
        else {
            results = tableApiMap[rel](lhs, rhs);
            resultExists = results.size();
        }
    }
}
