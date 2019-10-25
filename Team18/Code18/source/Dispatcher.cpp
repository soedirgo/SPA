#include "Dispatcher.h"
#include "AbstractType.h"
#include "Clause.h"
#include "PKB.h"
#include "Result.h"
#include <functional>
#include <string>
#include <unordered_map>

using namespace std;
namespace Evaluator {
    namespace {
        unordered_map<string, string> declarations;

        bool isUnderscore(string str) {
            return str == "_";
        }

        bool isIdentifier(string str) {
            return str.front() == '\"' || isdigit(str.front());
        }

        bool isPartialPattern(string str) {
            return !isUnderscore(str) && str.front() == '_';
        }

        string trimEnds(string str) {
            return str.substr(1, str.size() - 2);
        }

        string getEntity(string str) {
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
                                                        trimEnds(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isUsesPIdentAny(trimEnds(lhs));
                      else
                          return PKB::isUsesPIdentIdent(trimEnds(lhs),
                                                        trimEnds(rhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::isUsesPIdentAny(trimEnds(lhs));
                      else
                          return PKB::isUsesPIdentIdent(trimEnds(lhs),
                                                        trimEnds(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isUsesSIdentAny(lhs);
                      else
                          return PKB::isUsesSIdentIdent(lhs,
                                                        trimEnds(rhs));
          }},
         {"Modifies",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      if (isUnderscore(rhs))
                          return PKB::isModifiesSIdentAny(lhs);
                      else
                          return PKB::isModifiesSIdentIdent(lhs,
                                                            trimEnds(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isModifiesPIdentAny(trimEnds(lhs));
                      else
                          return PKB::isModifiesPIdentIdent(trimEnds(lhs),
                                                            trimEnds(rhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::isModifiesPIdentAny(trimEnds(lhs));
                      else
                          return PKB::isModifiesPIdentIdent(trimEnds(lhs),
                                                            trimEnds(rhs));
                  else
                      if (isUnderscore(rhs))
                          return PKB::isModifiesSIdentAny(lhs);
                      else
                          return PKB::isModifiesSIdentIdent(lhs,
                                                            trimEnds(rhs));
          }},
         {"Calls",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::isCallsAnyAny();
                  else
                      return PKB::isCallsAnyIdent(trimEnds(rhs));
              else
                  if (isUnderscore(rhs)) 
                      return PKB::isCallsIdentAny(trimEnds(lhs));
                  else
                      return PKB::isCallsIdentIdent(trimEnds(lhs),
                                                    trimEnds(rhs));
          }},
		 {"Calls*",
		  [](string lhs, string rhs) {
			  if (isUnderscore(lhs))
				  if (isUnderscore(rhs))
					  return PKB::isCallsTAnyAny();
				  else
					  return PKB::isCallsTAnyIdent(trimEnds(rhs));
			  else
				  if (isUnderscore(rhs))
					  return PKB::isCallsTIdentAny(trimEnds(lhs));
				  else
					  return PKB::isCallsTIdentIdent(trimEnds(lhs),
                                                     trimEnds(rhs));
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

        unordered_map<string, function<TABLE(string, string)>> suchThatTableApiMap =
        {{"Uses",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      return PKB::getUsesSIdentEnt(lhs);
                  else
                      return PKB::getUsesPIdentEnt(trimEnds(lhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::getUsesPEntAny();
                      else if (isIdentifier(rhs))
                          return PKB::getUsesPEntIdent(trimEnds(rhs));
                      else
                          return PKB::getUsesPEntEnt();
                  else
                      if (isUnderscore(rhs))
                          return PKB::getUsesSEntAny(getEntity(lhs));
                      else if (isIdentifier(rhs))
                          return PKB::getUsesSEntIdent(getEntity(lhs),
                                                       trimEnds(rhs));
                      else
                          return PKB::getUsesSEntEnt(getEntity(lhs));
          }},
         {"Modifies",
          [](string lhs, string rhs) {
              if (isIdentifier(lhs))
                  if (isdigit(lhs[0]))
                      return PKB::getModifiesSIdentEnt(lhs);
                  else
                      return PKB::getModifiesPIdentEnt(trimEnds(lhs));
              else
                  if (getEntity(lhs) == "procedure")
                      if (isUnderscore(rhs))
                          return PKB::getModifiesPEntAny();
                      else if (isIdentifier(rhs))
                          return PKB::getModifiesPEntIdent(trimEnds(rhs));
                      else
                          return PKB::getModifiesPEntEnt();
                  else
                      if (isUnderscore(rhs))
                          return PKB::getModifiesSEntAny(getEntity(lhs));
                      else if (isIdentifier(rhs))
                          return PKB::getModifiesSEntIdent(getEntity(lhs),
                                                           trimEnds(rhs));
                      else
                          return PKB::getModifiesSEntEnt(getEntity(lhs));
          }},
         {"Calls",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getCallsAnyEnt();
              else if (isIdentifier(lhs))
                  return PKB::getCallsIdentEnt(trimEnds(lhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getCallsEntAny();
                  else if (isIdentifier(rhs))
                      return PKB::getCallsEntIdent(trimEnds(rhs));
				  else if (lhs == rhs)
					  return TABLE();
                  else
                      return PKB::getCallsEntEnt();
          }},
		 {"Calls*",
		  [](string lhs, string rhs) {
			  if (isUnderscore(lhs))
				  return PKB::getCallsTAnyEnt();
			  else if (isIdentifier(lhs))
				  return PKB::getCallsTIdentEnt(trimEnds(lhs));
			  else
				  if (isUnderscore(rhs))
					  return PKB::getCallsTEntAny();
				  else if (isIdentifier(rhs))
					  return PKB::getCallsTEntIdent(trimEnds(rhs));
				  else if (lhs == rhs)
					  return TABLE();
				  else
					  return PKB::getCallsTEntEnt();
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
                      return TABLE();
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
                      return TABLE();
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
                      return TABLE();
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
                      return TABLE();
                  else
                      return PKB::getParentTEntEnt(getEntity(lhs),
                                                   getEntity(rhs));
          }},
         {"Next",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getNextAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getNextIdentEnt(lhs,
                                              getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getNextEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getNextEntIdent(getEntity(lhs), 
                                                  rhs);
                  else if (lhs == rhs)
                      return TABLE();
                  else
                      return PKB::getNextEntEnt(getEntity(lhs),
                                                getEntity(rhs));
          }},
         {"Next*",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getNextTAnyEnt(getEntity(rhs));
              else if (isIdentifier(lhs))
                  return PKB::getNextTIdentEnt(lhs,
                                               getEntity(rhs));
              else
                  if (isUnderscore(rhs))
                      return PKB::getNextTEntAny(getEntity(lhs));
                  else if (isIdentifier(rhs))
                      return PKB::getNextTEntIdent(getEntity(lhs), 
                                                   rhs);
                  else if (lhs == rhs)
                      return PKB::getNextTSelf(getEntity(lhs));
                  else
                      return PKB::getNextTEntEnt(getEntity(lhs),
                                                 getEntity(rhs));
          }}};

        unordered_map<string, function<TABLE(string, string)>> patternApiMap =
        {{"assign",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  if (isUnderscore(rhs))
                      return PKB::getPatternAssignAnyAny();
                  else if (isPartialPattern(rhs))
                      return PKB::getPatternAssignAnyPartial(trimEnds(rhs));
                  else
                      return PKB::getPatternAssignAnyFull(rhs);
              else if (isIdentifier(lhs))
                  if (isUnderscore(rhs))
                      return PKB::getPatternAssignIdentAny(trimEnds(lhs));
                  else if (isPartialPattern(rhs))
                      return PKB::getPatternAssignIdentPartial(trimEnds(lhs),
                                                               trimEnds(rhs));
                  else
                      return PKB::getPatternAssignIdentFull(trimEnds(lhs),
                                                            rhs);
              else
                  if (isUnderscore(rhs))
                      return PKB::getPatternAssignEntAny();
                  else if (isPartialPattern(rhs))
                      return PKB::getPatternAssignEntPartial(trimEnds(rhs));
                  else
                      return PKB::getPatternAssignEntFull(rhs);
          }},
         {"if",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getPatternIfAny();
              else if (isIdentifier(lhs))
                  return PKB::getPatternIfIdent(trimEnds(lhs));
              else
                  return PKB::getPatternIfEnt();
          }},
         {"while",
          [](string lhs, string rhs) {
              if (isUnderscore(lhs))
                  return PKB::getPatternWhileAny();
              else if (isIdentifier(lhs))
                  return PKB::getPatternWhileIdent(trimEnds(lhs));
              else
                  return PKB::getPatternWhileEnt();
          }}};

        auto withDispatcher =
            [](string lhs, string rhs) {
                size_t lhsPos = lhs.find('.');
                size_t rhsPos = rhs.find('.');
                if (lhsPos != string::npos)
                    if (rhsPos != string::npos)
                        return PKB::getWithAttrAttr(getEntity(lhs.substr(0, lhsPos)),
                                                    lhs.substr(lhsPos + 1, string::npos),
                                                    getEntity(rhs.substr(0, rhsPos)),
                                                    rhs.substr(rhsPos + 1, string::npos));
                    else if (isIdentifier(rhs))
                        return PKB::getWithIdentAttr((rhs.front() == '\"')
                                                     ? trimEnds(rhs)
                                                     : rhs,
                                                     getEntity(lhs.substr(0, lhsPos)),
                                                     lhs.substr(lhsPos + 1, string::npos));
                    else
                        return PKB::getWithAttrLine(getEntity(lhs.substr(0, lhsPos)),
                                                    lhs.substr(lhsPos + 1, string::npos));
                else if (isIdentifier(lhs))
                    if (rhsPos != string::npos)
                        return PKB::getWithIdentAttr((lhs.front() == '\"')
                                                     ? trimEnds(lhs)
                                                     : lhs,
                                                     getEntity(rhs.substr(0, rhsPos)),
                                                     rhs.substr(rhsPos + 1, string::npos));
                    else
                        return PKB::getWithIdentLine((lhs.front() == '\"')
                                                     ? trimEnds(lhs)
                                                     : lhs);
                else
                    if (rhsPos != string::npos)
                        return PKB::getWithAttrLine(getEntity(rhs.substr(0, rhsPos)),
                                                    rhs.substr(rhsPos + 1, string::npos));
                    else if (isIdentifier(rhs))
                        return PKB::getWithIdentLine((rhs.front() == '\"')
                                                     ? trimEnds(rhs)
                                                     : rhs);
                    else if (lhs == rhs)
                        return PKB::getProgLines();
                    else
                        return PKB::getWithLineLine();
            };
    }

    Result dispatch(Clause& clause,
                    unordered_map<string, string>& decl) {
        bool resultExists;
        unordered_map<string, int> synonyms;
        TABLE results;
        string type = clause.getType();
        vector<string> fields = clause.getFields();
        declarations = decl;

        for (const auto& field : fields)
            if (type == "such that" && field == fields[0])
                continue;
            else if (field.front() != ' ' && field.front() != '_' && field.front() != '\"'
                     && !isdigit(field.front()) && field.find('.') == string::npos)
                synonyms[field] = synonyms.size();
            else if (field.find('.') != string::npos) {
                size_t pos = field.find('.');
                synonyms[field.substr(0, pos)] = synonyms.size();
            }

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
        } else if (type == "with") {
            if (isIdentifier(fields[0]) && isIdentifier(fields[1]))
                resultExists = fields[0] == fields[1];
            else {
                results = withDispatcher(fields[0], fields[1]);
                resultExists = results.size();
            }
        } else {
            throw "Unexpected clause type";
        }

        return Result(resultExists, synonyms, results);
    }
} // namespace Evaluator
