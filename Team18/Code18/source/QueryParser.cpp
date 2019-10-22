using namespace std;

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <stack>

#include "Evaluator.h"
#include "Query.h"
#include "QueryParser.h"
#include "Clause.h"
#include "Validator.h"
#include <algorithm>

#include <iostream>
#include <sstream>
#include "PatternProcessor.h"

string whitespace = " ";
char whitespacech = ' ';
char whitespacech2 = '"';
int maxInt = numeric_limits<int>::max();
unordered_set<string> validTypes = { "stmt", "variable", "assign", "constant", "read", "while", "if",
"print", "call" , "prog_line" ,"procedure" };
unordered_set<string> validClauseType = { "Parent", "Parent*", "Follows",
		"Follows*", "Uses", "Modifies", "Calls", "Calls*", "Next", "Next*", "Affects", "Affects*" };
unordered_set<string> validArgs = { "stmt", "read", "print", "while", "if",
	"assign" ,"call", "prog_line" };
unordered_set<string> validFirstArgsParent = { "stmt", "while", "if","assign","print","read","prog_line" };
unordered_set<string> validFirstArgsUses = { "stmt", "print", "while", "if",
	"assign", "call", "procedure","prog_line" };
unordered_set<string> validFirstArgsModifies = { "stmt", "read", "while", "if",
"assign", "call","prog_line" ,"procedure"};
unordered_set<string> validSecondArgsUsesModifies = { "variable" };
unordered_set<string> validFirstSecondArgCall = { "procedure" };

Query QueryParser::parse(string query) {

	unordered_map<string, string> invalid1{ {"Invalidd", "Invalidd"} };
	vector<string> invalid2;
	invalid2.push_back("Invalidd");
	vector<string> invalid3;
	invalid3.push_back("Semantic Invalidd");
	vector<string> invalidstr;
	invalidstr.push_back("Invalidd");
	invalidstr.push_back("Invalidd");
	invalidstr.push_back("Invalidd");
	Clause invalidC = Clause("Invalidd", invalidstr);
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
	if (statements.empty()) {
		return invalidQ;
	}

	unordered_map<string, string> declerationVariables = splitVariablesInDeclerations(statements);
	
	resultString = declarationsValidation(declerationVariables);
	if (resultString == "Invalid" || resultString == "None") {
		return invalidQ;
	}
	
	string select = statements[statements.size() - 1];

	vector<string> selectVars;
	vector<pair<string, pair<string, string>>> suchThat;
	vector<pair<string, pair<string, string>>> pattern;

	vector<string> suchThatClauses;
	vector<string> patternClauses;

	//Finds the first occurance of such that and pattern in the string
	int suchThatIndex = select.find("such that ");
	int patternIndex = select.find("pattern ");
	int andIndex = maxInt;

	string previousClause;

	vector<int> indexes = { suchThatIndex, patternIndex};
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

	resultString = selectVariablesValidation(declerationVariables, selectVars);
	if (resultString == "Invalid") {
		return invalidQ;
	}

	//Find the next occurance of such that, push it to SuchThatClauses/PatternClauses. Continues till no more select statements
	while (select.length() > 0 && currentIndex != -1) {
		suchThatIndex = select.substr(1).find(" such that");
		patternIndex = select.substr(1).find(" pattern ");
		andIndex = select.substr(1).find(" and ");
		indexes = { suchThatIndex, patternIndex, andIndex};
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
		
		select = select.substr(currentIndex);
	}

	suchThat = splitSuchThat(suchThatClauses);
	pattern = splitPattern(patternClauses, declerationVariables);

	bool selectBoolean = false;
	if (selectVars.size() == 1 && selectVars[0] == "BOOLEAN") {
		selectBoolean = true;
	}

	resultString = suchThatValidation(declerationVariables, suchThat);
	if (resultString == "Invalid") {
		return invalidQ;
	}

	if (resultString == "Semantic Invalid" && selectBoolean == false) {
		return invalidQ;
	}

	if (resultString == "Semantic Invalid" && selectBoolean == true) {
		return semanticInvalidQ;
	}

	vector<Clause> clausesVector;

	for (int i = 0; i < suchThat.size(); i++) {
		vector<string> str;
		str.push_back(suchThat[i].first);
		str.push_back(suchThat[i].second.first);
		str.push_back(suchThat[i].second.second);
		
		Clause c = Clause("such that", str);
		clausesVector.push_back(c);
	}

	vector<string> patternStr;
	for (int j = 0; j < pattern.size(); j++) {
		patternStr.push_back(pattern[j].first);
		patternStr.push_back(pattern[j].second.first);
		patternStr.push_back(pattern[j].second.second);
		int x = patternStr.size() - 1;

		bool validationResult = Validator::isPatternValid(patternStr, declerationVariables);
		if (validationResult == false) {
			return semanticInvalidQ;
		}

		int flag3 = (patternStr[x].find('"') != -1);
		int flag4 = (patternStr[x].length() > 1);
		if (flag3 && flag4) {
			while (patternStr[x].find('"') != -1) {
				int index = patternStr[x].find('"');
				patternStr[x] = patternStr[x].erase(index, 1);
			}
		}

		Clause patternC = Clause("pattern", patternStr);
		clausesVector.push_back(patternC);
	}
	
	

	Query q = Query(declerationVariables, selectVars, clausesVector);
	return q;
}

//Finds delimiter ; and push initial declarations into a new vector and return the vector
vector<string> QueryParser::findInitialDecleration(string query) {
	char delimiter = ';';
	vector<string> stringVectors;
	int start = 0;
	int end = query.find(delimiter);

	//No delimiter ;
	if (end == -1) {
		stringVectors.push_back("");
		return stringVectors;
	}

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
		variableName = removeWhiteSpaces(statements.substr(firstSpace),whitespacech);
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
vector<pair<string, pair<string, string>>> QueryParser::splitPattern(vector<string> pattern, unordered_map<string, string> declerationVariables) {
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

		string patternType;
		if (declerationVariables.find(clauseType) != declerationVariables.end()) {
			patternType = declerationVariables.find(clauseType)->second;
		}

		string firstVar;
		string secondVar;
		if (patternType == "assign") {
			//Don't include _
			firstVar = trim(pattern[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket - 1), whitespace);
			string secondV = removeSpaces(pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma - 1), whitespace);
			int flag = (secondV.find("_") != -1);
			int flag2 = (secondV.length() > 1);
			if (flag && flag2) {
				while (secondV.find("_") != -1) {
					int index = secondV.find("_");
					secondV = secondV.erase(index,1);
				}
			}

			int flag3 = (secondV.find('"') != -1);
			int flag4 = (secondV.length() > 1);
			if (flag3 && flag4) {
				while (secondV.find('"') != -1) {
					int index = secondV.find('"');
					secondV = secondV.erase(index,1);
				}
			}

			secondV = removeWhiteSpaces(secondV, whitespacech);
			//Check if the second parameter is just "_"
			secondVar = secondV;
			if (!(secondV.size() == 1 && secondV.at(0) == '_')) {
				secondVar = PatternProcessor::infixtoRPNexpression(secondV);
			}

			if (flag3 && flag4) {
				secondVar.insert(0,1,'"');
				secondVar.insert(secondVar.length(), 1,'"');
			}

			if (flag && flag2) {
				secondVar.insert(0, "_");
				secondVar.insert(secondVar.length(), "_");
			}
		}

		else if (patternType == "while") {
			firstVar = trim(pattern[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket - 1), whitespace);
			secondVar = removeSpaces(pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma - 1), whitespace);
		}

		else if (patternType == "if") {
			firstVar = trim(pattern[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket - 1), whitespace);
			secondVar = removeSpaces(pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma - 1), whitespace);
			//From secondVar have to make a thirdVar out
		}
	

		s.push_back(make_pair(clauseType, make_pair(firstVar, secondVar)));
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
	s.erase(0, s.find_first_not_of(whitespace));
	s.erase(s.find_last_not_of(whitespace) + 1);
	return s;
}

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
	//unordered_set<string> validTypes = { "stmt", "variable", "assign", "constant", "read", "while", "if", "print", "procedure" };

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
			//procName seems to accept only procedure and call
			if (right == "procName" && (typesForProcName.find(synonymType) != typesForProcName.end())) {
				continue;
			}
			else if (right == "varName" && (typesForVarName.find(synonymType) != typesForVarName.end())) {
				continue;
			}
			
			//Seems to accept constant
			else if (right == "value" && (typesForValue.find(synonymType) != typesForValue.end())) {
				continue;
			}
			
			//Seems to accept statement, assign and the like
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
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_" || validArgs.find(secondArgsType) != validArgs.end()) {
				// valid second args
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}
		}
		else if (suchThat[i].first == "Follows" || suchThat[i].first == "Follows*" || suchThat[i].first == "Next" || suchThat[i].first == "Next*") {

			// Validating first args
			if (suchThat[i].second.first == "_" || validArgs.find(firstArgsType) != validArgs.end()) {
				// valid first args
			}

			else if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}

			else {
				resultString = "Semantic Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_" || validArgs.find(secondArgsType) != validArgs.end()) {
				// valid second args
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}

			else {
				resultString = "Semantic Invalid";
				return resultString;
			}
		}
		else if (suchThat[i].first == "Uses") {

			if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.first[0] == '"') {
				string name = suchThat[i].second.first.substr(1, suchThat[i].second.first.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.first[0] != '"' && (validFirstArgsUses.find(firstArgsType) != validFirstArgsUses.end()))) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}

			// Validating second args
			if(suchThat[i].second.second == "_") {
				//valid
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.second[0] == '"') {
				string name = suchThat[i].second.second.substr(1, suchThat[i].second.second.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.second[0] != '"' && (validSecondArgsUsesModifies.find(secondArgsType) != validSecondArgsUsesModifies.end()))) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}
		}
		else if (suchThat[i].first == "Modifies") {

			if (isdigit(suchThat[i].second.first[0])) {
				for (size_t j = 0; j < suchThat[i].second.first.length(); j++) {
					if (!isdigit(suchThat[i].second.first[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.first) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.first[0] == '"') {
				string name = suchThat[i].second.first.substr(1, suchThat[i].second.first.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else if ((suchThat[i].second.first[0] != '"' && (validFirstArgsModifies.find(firstArgsType) != validFirstArgsModifies.end()))) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_") {
				//valid
			}

			else if (isdigit(suchThat[i].second.second[0])) {
				for (size_t j = 0; j < suchThat[i].second.second.length(); j++) {
					if (!isdigit(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

				if (!(std::stoi(suchThat[i].second.second) > 0)) {
					resultString = "Semantic Invalid";
					return resultString;
				}
			}

			else if (suchThat[i].second.second[0] == '"') {
				string name = suchThat[i].second.second.substr(1, suchThat[i].second.second.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.second[0] != '"' && (validSecondArgsUsesModifies.find(secondArgsType) != validSecondArgsUsesModifies.end()))) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Semantic Invalid";
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
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else if ((suchThat[i].second.first[0] != '"' && validFirstSecondArgCall.find(firstArgsType) != validFirstSecondArgCall.end())) {
				if (!isalpha(suchThat[i].second.first[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.first.length(); j++) {
					if (!isalnum(suchThat[i].second.first[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}

			// Validating second args
			if (suchThat[i].second.second == "_") {
				//valid
			}

			else if (suchThat[i].second.second[0] == '"') {
				string name = suchThat[i].second.second.substr(1, suchThat[i].second.second.length() - 2);

				if (!isalpha(name[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < name.length(); j++) {
					if (!isalnum(name[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}

			}

			else if ((suchThat[i].second.second[0] != '"' && validFirstSecondArgCall.find(secondArgsType) != validFirstSecondArgCall.end())) {
				if (!isalpha(suchThat[i].second.second[0])) {
					resultString = "Semantic Invalid";
					return resultString;
				}

				//Rest must be alphabets or numbers
				for (int j = 1; j < suchThat[i].second.second.length(); j++) {
					if (!isalnum(suchThat[i].second.second[j])) {
						resultString = "Semantic Invalid";
						return resultString;
					}
				}
			}
			else {
				resultString = "Semantic Invalid";
				return resultString;
			}
		}
	}
	return resultString;
}