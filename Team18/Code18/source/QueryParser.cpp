#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "Clause.h"
#include "Evaluator.h"
#include "PatternProcessor.h"
#include "Query.h"
#include "QueryParser.h"
#include "Validator.h"

using namespace std;
string whitespace = " ";
char whitespacech = ' ';
char whitespacech2 = '"';
int maxInt = numeric_limits<int>::max();
unordered_set<string> validTypes = { "stmt", "variable", "assign", "constant", "read", "while", "if",
"print", "call" , "prog_line" ,"procedure" };
unordered_set<string> validClauseType = { "Parent", "Parent*", "Follows",
		"Follows*", "Uses", "Modifies", "Calls", "Calls*", "Next", "Next*", "NextBip","NextBip*","Affects", "Affects*", "AffectsBip","AffectsBip*"};
unordered_set<string> validArgs = { "stmt", "read", "print", "while", "if",
	"assign" ,"call", "prog_line" };
unordered_set<string> validFirstArgsParent = { "stmt", "while", "if","assign","print","read","prog_line" };
unordered_set<string> validFirstArgsUses = { "stmt", "print", "while", "if",
	"assign", "call", "procedure","prog_line" };
unordered_set<string> validFirstArgsModifies = { "stmt", "read", "while", "if",
"assign", "call","prog_line" ,"procedure"};
unordered_set<string> validSecondArgsUsesModifies = { "variable" };
unordered_set<string> validFirstSecondArgCall = { "procedure" };
unordered_set<string> validArgsAffects = { "assign","stmt","prog_line" };

Query QueryParser::parse(string query) {
	//Initialize an Invalid Query & Semantic Invalid Query to be returned if query is invalid/semantically invalid
	unordered_map<string, string> invalid1{ {"Invalid", "Invalid"} };
	vector<string> invalid2;
	invalid2.push_back("Invalid");
	vector<string> invalid3;
	invalid3.push_back("Semantic Invalid");
	vector<string> invalidstr;
	invalidstr.push_back("Invalid");
	invalidstr.push_back("Invalid");
	invalidstr.push_back("Invalid");
	Clause invalidC = Clause("Invalid", invalidstr);
	vector<Clause> invalidCVector;
	invalidCVector.push_back(invalidC);

	Query invalidQ = Query(invalid1,invalid2,invalidCVector);
	Query semanticInvalidQ = Query(invalid1, invalid3, invalidCVector);
	
	string resultString;

	resultString = initialValidation(query);
	if (resultString == "Invalid" || resultString == "None") {
		return invalidQ;
	}

	vector<string> statements = findInitialDecleration(query);

	unordered_map<string, string> declerationVariables = splitVariablesInDeclerations(statements);
	
	resultString = declarationsValidation(declerationVariables);
	if (resultString == "Invalid" || resultString == "None") {
		return invalidQ;
	}
	
	string select = statements[statements.size() - 1];

	vector<string> selectVars;
	vector<pair<string, pair<string, string>>> suchThat;
	vector<pair<string, pair<string, string>>> pattern;
	vector<pair<string, string>> with;

	vector<string> suchThatClauses;
	vector<string> patternClauses;
	vector<string> withClauses;

	//Finds the first occurance of such that and pattern in the string
	int suchThatIndex = select.find("such that ");
	int patternIndex = select.find("pattern ");
	int andIndex = maxInt;
	int withIndex = select.find("with ");

	string previousClause;

	vector<int> indexes = { suchThatIndex, patternIndex, withIndex};
	int currentIndex = getMinimumIndex(indexes);

	//Only have select variables
	if (currentIndex == -1) {
		selectVars = splitSelect(select);
	}

	//Split the word select out and remove it away from the select string
	else {
		string str = select.substr(0, currentIndex);
		selectVars = splitSelect(str);
		select = select.substr(currentIndex);
	}

	//Find the next occurance of such that, push it to SuchThatClauses/PatternClauses/With Clauses. Continues till no more statements
	while (select.length() > 0 && currentIndex != -1) {
		suchThatIndex = select.substr(1).find(" such that");
		patternIndex = select.substr(1).find(" pattern ");
		andIndex = select.substr(1).find(" and ");
		withIndex = select.substr(1).find(" with ");
		indexes = { suchThatIndex, patternIndex, andIndex , withIndex};
		currentIndex = getMinimumIndex(indexes) + 1;

		if (currentIndex == 0) {
			currentIndex = select.length();
		}

		else {
			currentIndex = currentIndex + 1;
		}

		string currentClause = select.substr(0, currentIndex);
		if (currentClause.find("such that ") != -1 || (currentClause.find("and ") != -1 && previousClause == "such that")) {
			previousClause = "such that";
			suchThatClauses.push_back(currentClause);
		}

		else if (currentClause.find("pattern ") != -1 || (currentClause.find("and ") != -1 && previousClause == "pattern")) {
			previousClause = "pattern";
			patternClauses.push_back(currentClause);
		}
		
		else if (currentClause.find("with ") != -1 || (currentClause.find("and ") != -1 && previousClause == "with")) {
			previousClause = "with";
			withClauses.push_back(currentClause);
		}

		select = select.substr(currentIndex);
	}

	suchThat = splitSuchThat(suchThatClauses);
	pattern = splitPattern(patternClauses);
	with = splitWith(withClauses);

	bool selectBoolean = false;
	if (selectVars.size() == 1 && selectVars[0] == "BOOLEAN") {
		selectBoolean = true;
	}

	resultString = selectVariablesValidation(declerationVariables, selectVars);
	if (resultString == "Invalid") {
		if (selectBoolean) {
			return semanticInvalidQ;
		}
		return invalidQ;
	}

	resultString = suchThatValidation(declerationVariables, suchThat);
	if (resultString == "Invalid") {
		if (selectBoolean) {
			return semanticInvalidQ;
		}
		return invalidQ;
	}

	resultString = withValidation(declerationVariables, with);
	if (resultString == "Invalid") {
		if (selectBoolean) {
			return semanticInvalidQ;
		}
		return invalidQ;
	}

	vector<Clause> clausesVector;

	//Make a clause object to be inserted into query object later
	for (int i = 0; i < suchThat.size(); i++) {
		vector<string> str;
		str.push_back(suchThat[i].first);
		str.push_back(suchThat[i].second.first);
		str.push_back(suchThat[i].second.second);
		
		Clause c = Clause("such that", str);
		clausesVector.push_back(c);
	}

	//Make a clause object to be inserted into query object later
	for (int j = 0; j < pattern.size(); j++) {
		vector<string> patternStr;
		patternStr.push_back(pattern[j].first);
		patternStr.push_back(pattern[j].second.first);
		patternStr.push_back(pattern[j].second.second);

		bool validationResult = Validator::isPatternValid(patternStr, declerationVariables);
		if (validationResult == false) {
			if (selectBoolean) {
				return semanticInvalidQ;
			}
			return invalidQ;
		}

		string patternType;
		if (declerationVariables.find(pattern[j].first) != declerationVariables.end()) {
			patternType = declerationVariables.find(pattern[j].first)->second;
		}

		//Checks for expression to be valid first. If is valid, expression will go through Shunting Yard algorithm 
		if (patternType == "assign") {
			string secondV = pattern[j].second.second;
			int flag = (secondV.find("_") != -1);
			int flag2 = (secondV.length() > 1);
			int countUnderScore = 0;
			if (flag && flag2) {
				while (secondV.find("_") != -1) {
					int index = secondV.find("_");
					secondV = secondV.erase(index, 1);
					countUnderScore = countUnderScore + 1;
				}
			}

			int flag3 = (secondV.find('"') != -1);
			int flag4 = (secondV.length() > 1);
			int countQuote = 0;
			if (flag3 && flag4) {
				while (secondV.find('"') != -1) {
					int index = secondV.find('"');
					secondV = secondV.erase(index, 1);
					countQuote = countQuote + 1;
				}
			}

			secondV = removeWhiteSpaces(secondV, whitespacech);

			//Check if the second parameter is just "_"
			if (!(secondV.size() == 1 && secondV.at(0) == '_')) {
				if (!Validator::isExprSpecValid(secondV)) {
					if (selectBoolean) {
						return semanticInvalidQ;
					}
					return invalidQ;
				}
				secondV = PatternProcessor::infixtoRPNexpression(secondV);
			}

			if (flag && flag2 && countUnderScore == 2) {
				secondV.insert(0, "_");
				secondV.insert(secondV.length(), "_");
			}

			patternStr.pop_back();
			patternStr.push_back(secondV);
		}

		Clause patternC = Clause("pattern", patternStr);
		clausesVector.push_back(patternC);
	}

	//Make a clause object to be inserted into query object later
	for (int k = 0; k < with.size(); k++) {
		vector<string> str;
		str.push_back(with[k].first);
		str.push_back(with[k].second);

		Clause withC = Clause("with", str);
		clausesVector.push_back(withC);
	}

	//Initializes a query object based on declarations map, variables in select and all the clauses
	Query q = Query(declerationVariables, selectVars, clausesVector);
	return q;
}

//Finds delimiter ; and push initial declarations into a new vector and return the vector
vector<string> QueryParser::findInitialDecleration(string query) {
	char delimiter = ';';
	vector<string> stringVectors;
	int start = 0;
	int end = query.find(delimiter);

	while (end != -1) {
		string trimmed = trim(query.substr(start, end - start), whitespace);
		stringVectors.push_back(trimmed);

		start = end + 1;
		end = query.find(delimiter, start);
	}
	string trimmed2 = trim(query.substr(start), whitespace);
	stringVectors.push_back(trimmed2);

	return stringVectors;
}

//For the purpose of mapping variable to what it's declared for
unordered_map<string, string> QueryParser::splitVariablesInDeclerations(vector<string> declerations) {
	unordered_map<string, string> taggedDeclerationVariables;
	int declerationsSize = declerations.size();
	int i;
	int posWhiteSpace;
	string declarationType;
	string variableName;
	for (i = 0; i < declerationsSize - 1; i++) {
		string currentDeclerations = declerations[i];
		posWhiteSpace = currentDeclerations.find_first_of(whitespace);
		declarationType = currentDeclerations.substr(0, posWhiteSpace);
		variableName = currentDeclerations.substr(posWhiteSpace);

		if (variableName.find(",") != -1) {
			char delimiter = ',';
			int start = 0;
			int end = variableName.find(delimiter);

			while (end != -1) {
				string variableNameSplitted = trim(variableName.substr(start, end - start), whitespace);
				taggedDeclerationVariables.insert(make_pair(variableNameSplitted, declarationType));
				start = end + 1;
				end = variableName.find(delimiter, start);
			}

			taggedDeclerationVariables.insert(make_pair(trim(variableName.substr(start), whitespace), declarationType));
		}
		else {
			taggedDeclerationVariables.insert(make_pair(trim(variableName, whitespace), declarationType));
		}
	}

	return taggedDeclerationVariables;
}

//Split by whitespace
vector<string> QueryParser::splitSelect(string statements) {
	vector<string> str;
	int firstSpace = statements.find_first_of(whitespace);
	string variableName;

	if (firstSpace != -1) {
		variableName = removeSpaces(statements.substr(firstSpace),whitespace);
	}

	//To handle Tuple
	if (variableName.find("<") != -1 && variableName.find(">") != -1) {
		variableName = variableName.substr(1, variableName.length() - 2);

		while (variableName.find(",") != -1) {
			int comma = variableName.find(",");
			str.push_back(variableName.substr(0, comma));
			variableName = variableName.substr(comma + 1);
		}
	}
	str.push_back(variableName);

	return str;
}


//Split by brackets
vector<pair<string, pair<string, string>>> QueryParser::splitSuchThat(vector<string> suchThat) {
	vector<pair<string, pair<string, string>>> s;
	int i = 0;
	int posOfOpenBracket;
	int posOfComma;
	int posOfCloseBracket;
	int lengthofString;
	string clauseType;
	for (i = 0; i < suchThat.size(); i++) {
		posOfOpenBracket = suchThat[i].find("(");
		posOfCloseBracket = suchThat[i].find(")");
		posOfComma = suchThat[i].find(",");
		
		if (posOfOpenBracket == -1 || posOfComma == -1 || posOfCloseBracket == -1) {
			s.push_back(make_pair("", make_pair("", "")));
			continue;
		}

		if (suchThat[i].find("such") != -1) {
			clauseType = removeSpaces(suchThat[i].substr(9, posOfOpenBracket - 9), whitespace);
		}
		else {
			clauseType = removeSpaces(suchThat[i].substr(3, posOfOpenBracket - 3), whitespace);
		}

		string firstVar;
		string secondVar;

		if ((posOfComma - posOfOpenBracket - 1) < 0) {
			firstVar = "";
		}
		else {
			firstVar = removeSpaces(suchThat[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket - 1), whitespace);
		}

		if ((posOfCloseBracket - posOfComma - 1) < 0) {
			secondVar = "";
		}
		else {
			secondVar = removeSpaces(suchThat[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma - 1), whitespace);
		}

		s.push_back(make_pair(clauseType, make_pair(firstVar, secondVar)));
	}

	return s;
}

//Split by brackets
vector<pair<string, pair<string, string>>> QueryParser::splitPattern(vector<string> pattern) {
	vector<pair<string, pair<string, string>>> s;
	int i = 0;
	int posOfOpenBracket;
	int posOfComma;
	int posOfCloseBracket;
	int lengthofString;
	string clauseType;
	for (i = 0; i < pattern.size(); i++) {
		posOfOpenBracket = pattern[i].find_first_of("(");
		posOfCloseBracket = pattern[i].find_last_of(")");
		posOfComma = pattern[i].find(",");

		if (pattern[i].find("pattern") != -1) {
			clauseType = trim(pattern[i].substr(7, posOfOpenBracket - 7), whitespace);
		}
		else {
			clauseType = trim(pattern[i].substr(3, posOfOpenBracket - 3), whitespace);
		}

		string firstVar;
		string secondVar;

		//Don't include _
		firstVar = removeSpaces(pattern[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket - 1), whitespace);
		secondVar = removeSpaces(pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma - 1), whitespace);

		s.push_back(make_pair(clauseType, make_pair(firstVar, secondVar)));
	}

	return s;
}

//Split by = sign
vector<pair<string, string>> QueryParser::splitWith(vector<string> with) {
	vector<pair<string, string>> s;
	int i = 0;
	string clauseType;
	for (i = 0; i < with.size(); i++) {
		int lengthofString = with[i].length();
		int equalSignIndex = with[i].find("=");
		string firstVar;
		string secondVar;

		if (with[i].find("with") != -1) {
			firstVar = removeSpaces(with[i].substr(4, equalSignIndex - 4), whitespace);
		}
		else {
			firstVar = removeSpaces(with[i].substr(3, equalSignIndex - 3), whitespace);
		}

		secondVar = removeSpaces(with[i].substr(equalSignIndex + 1), whitespace);

		s.push_back(make_pair(firstVar, secondVar));
	}

	return s;
}

//Trims front and back of the str with the given whitespace.
string QueryParser::trim(string str, string whitespace) {
	int start = str.find_first_not_of(whitespace);
	int end = str.find_last_not_of(whitespace);

	if (start == string::npos) {
		return "";
	}

	int length = end - start + 1;
	return str.substr(start, length);
}

//Removes all the whitespace in the given string
string QueryParser::removeSpaces(string s, string whitespace) {
	int a = 0;
	while (a < s.length()) {
		if (s[a] == whitespacech || s[a] == '\t' || s[a] == '\r' || s[a] == '\n' || s[a] == '\v' || s[a] == '\f') {
			s.erase(a, 1);
			continue;
		}
		a++;
	}

	return s;
}

//Remove all whitespace and quotes in the given string for pattern assign expression
string QueryParser::removeWhiteSpaces(string s, char whitespace) {
	int a = 0;
	while (a < s.length()) {
		if (s[a] == whitespacech || s[a] == whitespacech2) {
			s.erase(a,1);
			continue;
		}
		a++;
	}

	return s;
}

int QueryParser::getMinimumIndex(vector<int> indexes) {

	int minIndex = maxInt;
	for (int i = 0; i < indexes.size(); i++) {
		if (indexes[i] != -1 && indexes[i] < minIndex) {
			minIndex = indexes[i];
		}
	}

	if (minIndex == maxInt) {
		return -1;
	}
	else {
		return minIndex;
	}
}

string QueryParser::initialValidation(string query) {

	string resultString = "Okay";
	//Empty query
	if (query.empty()) {
		resultString = "Invalid";
		return resultString;
	}

	//Select is at the start of the query, no declarations and it's not select BOOLEAN
	else if (query.find("Select") == 0 && query.find("BOOLEAN") == -1) {
		resultString = "None";
		return resultString;
	}

	//Only declarations with no select
	else if (query.find("Select") == -1) {
		resultString = "Invalid";
		return resultString;
	}

	return resultString;
}

string QueryParser::declarationsValidation(unordered_map<string, string> declerationVariables) {
	string resultString = "Okay";

	//Iterate through the map of declaration variables and see if there's anything invalid
	for (auto iterator : declerationVariables) {
		//Not a valid type/Typos in declaration Type
		if (validTypes.find(iterator.second) == validTypes.end()) {
			resultString = "Invalid";
			return resultString;
		}

		//Declarations that doesn't have variable
		if (iterator.first.empty()) {
			resultString = "Invalid";
			return resultString;
		}

		//First character not alphabet
		if (!isalpha(iterator.first[0])) {
			resultString = "Invalid";
			return resultString;
		}

		//Rest must be alphabets or numbers
		for (int i = 1; i < iterator.first.length(); i++) {
			if (!isalnum(iterator.first[i])) {
				resultString = "Invalid";
				return resultString;
			}
		}
	}

	return resultString;
}

string QueryParser::selectVariablesValidation(unordered_map<string, string> declerationVariables, vector<string> selectVars) {

	string resultString = "Okay";

	unordered_set<string> typesForProcName = { "call", "procedure" };
	unordered_set<string> typesForVarName = { "variable", "read", "print" };
	unordered_set<string> typesForValue = { "constant" };
	unordered_set<string> typesForStmtNum = { "stmt", "assign", "while", "read", "print", "if", "call" };

	//No variables to select
	if (selectVars.empty()) {
		resultString = "Invalid";
		return resultString;
	}

	for (int i = 0; i < selectVars.size(); i++) {

		//Select Boolean can't have other select variables inside tuple of selects
		if (selectVars[i] == "BOOLEAN" && selectVars.size() != 1) {
			resultString = "Invalid";
			return resultString;
		}
	
		//Select Variables that have things like p.procName etc
		if (selectVars[i].find(".") != -1) {
			int dotIndex = selectVars[i].find(".");
			string left = selectVars[i].substr(0, dotIndex);
			string right = selectVars[i].substr(dotIndex + 1, selectVars[i].length() - dotIndex - 1);

			if (declerationVariables.find(left) == declerationVariables.end()) {
				resultString = "Invalid";
				return resultString;
			}

			string synonymType = declerationVariables.find(left)->second;

			//Checks for validity
			//attrName can be "procName", "varName", "value","stmt#"
			//procName accept only procedure and call
			if (right == "procName" && (typesForProcName.find(synonymType) != typesForProcName.end())) {
				continue;
			}
			else if (right == "varName" && (typesForVarName.find(synonymType) != typesForVarName.end())) {
				continue;
			}
			
			else if (right == "value" && (typesForValue.find(synonymType) != typesForValue.end())) {
				continue;
			}
			
			else if (right == "stmt#" && (typesForStmtNum.find(synonymType) != typesForStmtNum.end())) {
				continue;
			}
			
			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		//First character not alphabet
		else if (!isalpha(selectVars[i][0])) {
			resultString = "Invalid";
			return resultString;
		}

		//Rest must be alphabets or numbers
		for (int j = 1; j < selectVars[i].length(); j++) {
			if (!isalnum(selectVars[i][j])) {
				resultString = "Invalid";
				return resultString;
			}
		}

		if (selectVars[i] != "BOOLEAN" &&
			declerationVariables.find(selectVars[i]) == declerationVariables.end()) {
			resultString = "Invalid";
			return resultString;
		}
	}
	
	return resultString;
}
//Function validates such that clauses based on its clause type and checks against a list of valid types in the arguments
string QueryParser::suchThatValidation(unordered_map<string, string> declerationVariables, vector<pair<string, pair<string, string>>> suchThat) {
	string resultString = "Okay";
	string firstArgsType;
	string secondArgsType;
	int i;
	int j;
	for (i = 0; i < suchThat.size(); i++) {
		//Empty variable or clause
		if ((suchThat[i].first == "") || (suchThat[i].second.first == "") || (suchThat[i].second.second == "")) {
			resultString = "Invalid";
			return resultString;
		}

		if (validClauseType.find(suchThat[i].first) == validClauseType.end()) {
			resultString = "Invalid";
			return resultString;
		}

		if (declerationVariables.find(suchThat[i].second.first) != declerationVariables.end()) {
			firstArgsType = declerationVariables.find(suchThat[i].second.first)->second;
		}

		if (declerationVariables.find(suchThat[i].second.second) != declerationVariables.end()) {
			secondArgsType = declerationVariables.find(suchThat[i].second.second)->second;
		}

		if (suchThat[i].first == "Parent" || suchThat[i].first == "Parent*") {

			// Validating first args
			if (suchThat[i].second.first == "_" || validFirstArgsParent.find(firstArgsType) != validFirstArgsParent.end()) {
				// valid first args
			}

			else if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_" || validArgs.find(secondArgsType) != validArgs.end()) {
				// valid second args
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}
		else if (suchThat[i].first == "Follows" || suchThat[i].first == "Follows*" || suchThat[i].first == "Next" || suchThat[i].first == "Next*" || suchThat[i].first == "NextBip" || suchThat[i].first == "NextBip*") {

			// Validating first args
			if (suchThat[i].second.first == "_" || validArgs.find(firstArgsType) != validArgs.end()) {
				// valid first args
			}

			else if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else {
				resultString = "Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_" || validArgs.find(secondArgsType) != validArgs.end()) {
				// valid second args
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}
		else if (suchThat[i].first == "Uses") {

			if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.first[0] == '"') {
				string name = suchThat[i].second.first.substr(1, suchThat[i].second.first.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.first[0] != '"' && (validFirstArgsUses.find(firstArgsType) != validFirstArgsUses.end()))) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			// Validating second args
			if(suchThat[i].second.second == "_") {
				//valid
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.second[0] == '"') {
				string name = suchThat[i].second.second.substr(1, suchThat[i].second.second.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.second[0] != '"' && (validSecondArgsUsesModifies.find(secondArgsType) != validSecondArgsUsesModifies.end()))) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}
		else if (suchThat[i].first == "Modifies") {

			if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.first[0] == '"') {
				string name = suchThat[i].second.first.substr(1, suchThat[i].second.first.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else if ((suchThat[i].second.first[0] != '"' && (validFirstArgsModifies.find(firstArgsType) != validFirstArgsModifies.end()))) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_") {
				//valid
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.second[0] == '"') {
				string name = suchThat[i].second.second.substr(1, suchThat[i].second.second.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.second[0] != '"' && (validSecondArgsUsesModifies.find(secondArgsType) != validSecondArgsUsesModifies.end()))) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (suchThat[i].first == "Calls" || suchThat[i].first == "Calls*") {
			// Validating first args
			if (suchThat[i].second.first == "_") {
				// valid first args
			}

			else if (suchThat[i].second.first[0] == '"') {
				string name = suchThat[i].second.first.substr(1, suchThat[i].second.first.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else if ((suchThat[i].second.first[0] != '"' && validFirstSecondArgCall.find(firstArgsType) != validFirstSecondArgCall.end())) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_") {
				//valid
			}

			else if (suchThat[i].second.second[0] == '"') {
				string name = suchThat[i].second.second.substr(1, suchThat[i].second.second.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.second[0] != '"' && validFirstSecondArgCall.find(secondArgsType) != validFirstSecondArgCall.end())) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (suchThat[i].first == "Affects" || suchThat[i].first == "Affects*" || suchThat[i].first == "AffectsBip" || suchThat[i].first == "AffectsBip*") {
			
			if (suchThat[i].second.first == "_") {
				//valid
			}

			else if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else if (validArgsAffects.find(firstArgsType) != validArgsAffects.end()) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_") {
				//valid
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Invalid";
					return resultString;
				}
			}

			else if (validArgsAffects.find(secondArgsType) != validArgsAffects.end()) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}
	}
	return resultString;
}

string QueryParser::withValidation(unordered_map<string, string> declerationVariables, vector<pair<string, string>> with) {
	string resultString = "Okay";

	unordered_set<string> typesForProcName = { "procedure","call" };
	unordered_set<string> typesForVarName = { "variable", "read", "print"};
	unordered_set<string> typesForIntValue = { "constant" };
	unordered_set<string> typesForIntStmt = { "stmt", "read", "print","call","while","if","assign"};
	unordered_set<string> typesForInt = { "prog_line" };

	for (int i = 0; i < with.size(); i++) {
		string left = with[i].first;
		string right = with[i].second;
		string synonym;
		string synonymType;
		string leftType = "";
		string rightType = "";

		if (isdigit(left[0])) {
			int intflagLeft = 1;
			for (size_t j = 0; j < left.length(); j++) {
				if (!isdigit(left[j])) {
					intflagLeft = 0;
				}
			}
			if (intflagLeft) {
				leftType = "int";
			}
		}

		//Find type for the left
		else if (left.find(".stmt#") != -1) {
			synonym = left.substr(0, left.find("."));
			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
			
			if (typesForIntStmt.find(synonymType) != typesForIntStmt.end()) {
				leftType = "int";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (left.find(".value") != -1) {
			synonym = left.substr(0, left.find("."));
			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForIntValue.find(synonymType) != typesForIntValue.end()) {
				leftType = "int";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (left.find(".procName") != -1) {
			synonym = left.substr(0, left.find("."));
			
			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForProcName.find(synonymType) != typesForProcName.end()) {
				leftType = "str";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (left.find(".varName") != -1) {
			synonym = left.substr(0, left.find("."));

			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForVarName.find(synonymType) != typesForVarName.end()) {
				leftType = "str";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (isalpha(left[0])) {
			//Rest must be alphabets or numbers
			for (int j = 1; j < left.length(); j++) {
				if (!(isalnum(left[j]))) {
					resultString = "Invalid";
					return resultString;
				}
			}

			if (declerationVariables.find(left) != declerationVariables.end()) {
				synonymType = declerationVariables.find(left)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForInt.find(synonymType) != typesForInt.end()) {
				leftType = "int";
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (left[0] == '"') {
			string name = left.substr(1, left.length() - 2);

			if (!isalpha(name[0])) {
				resultString = "Invalid";
				return resultString;
			}

			//Rest must be alphabets or numbers
			for (int j = 1; j < name.length(); j++) {
				if (!isalnum(name[j])) {
					resultString = "Invalid";
					return resultString;
				}
			}

			leftType = "str";
		}

		if (isdigit(right[0])) {
			int intflagRight = 1;
			for (size_t j = 0; j < right.length(); j++) {
				if (!isdigit(right[j])) {
					intflagRight = 0;
				}
			}
			if (intflagRight) {
				rightType = "int";
			}
		}

		//Find type for the right
		else if (right.find(".stmt#") != -1) {
			synonym = right.substr(0, right.find("."));
			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForIntStmt.find(synonymType) != typesForIntStmt.end()) {
				rightType = "int";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (right.find(".value") != -1) {
			synonym = right.substr(0, right.find("."));
			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForIntValue.find(synonymType) != typesForIntValue.end()) {
				rightType = "int";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (right.find(".procName") != -1) {
			synonym = right.substr(0, right.find("."));

			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForProcName.find(synonymType) != typesForProcName.end()) {
				rightType = "str";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (right.find(".varName") != -1) {
			synonym = right.substr(0, right.find("."));

			if (declerationVariables.find(synonym) != declerationVariables.end()) {
				synonymType = declerationVariables.find(synonym)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForVarName.find(synonymType) != typesForVarName.end()) {
				rightType = "str";
			}

			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (isalpha(right[0])) {
			//Rest must be alphabets or numbers
			for (int j = 1; j < right.length(); j++) {
				if (!(isalnum(right[j]) || right[j] == '#')) {
					resultString = "Invalid";
					return resultString;
				}
			}

			if (declerationVariables.find(right) != declerationVariables.end()) {
				synonymType = declerationVariables.find(right)->second;
			}
			else {
				resultString = "Invalid";
				return resultString;
			}

			if (typesForInt.find(synonymType) != typesForInt.end()) {
				rightType = "int";
			}
			else {
				resultString = "Invalid";
				return resultString;
			}
		}

		else if (right[0] == '"') {
			string name = right.substr(1, right.length() - 2);

			if (!isalpha(name[0])) {
				resultString = "Invalid";
				return resultString;
			}

			//Rest must be alphabets or numbers
			for (int j = 1; j < name.length(); j++) {
				if (!isalnum(name[j])) {
					resultString = "Invalid";
					return resultString;
				}
			}

			rightType = "str";
		}

		if (leftType == "" || rightType == "" || leftType != rightType) {
			resultString = "Invalid";
			return resultString;
		}
	}
	
	return resultString;
}