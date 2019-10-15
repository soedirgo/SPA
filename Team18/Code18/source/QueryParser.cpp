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
#include <algorithm>

#include <iostream>
#include <sstream>

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

	unordered_map<string, string> invalid1{ {"Invalid", "Invalid"} };
	string invalid2 = "Invalid";
	vector<string> invalidstr;
	invalidstr.push_back("Invalid");
	invalidstr.push_back("Invalid");
	invalidstr.push_back("Invalid");
	Clause invalidC = Clause("Invalid", invalidstr);
	vector<Clause> invalidCVector;
	invalidCVector.push_back(invalidC);

	Query invalidQ = Query(invalid1,invalid2,invalidCVector);
	
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

	string selectVars;
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

		string currentClause = select.substr(0, suchThatIndex);
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
	pattern = splitPattern(patternClauses);

	resultString = suchThatValidation(declerationVariables, suchThat);
	if (resultString == "Invalid") {
		return invalidQ;
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

	for (int j = 0; j < pattern.size(); j++) {
		vector<string> patternStr;
		patternStr.push_back(pattern[j].first);
		patternStr.push_back(pattern[j].second.first);
		patternStr.push_back(pattern[j].second.second);

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
string QueryParser::splitSelect(string statements) {
	string str;
	int firstSpace = statements.find_first_of(whitespace);
	string variableName;

	if (firstSpace != -1) {
		variableName = removeSpaces(statements.substr(firstSpace), whitespace);
	}

	str = variableName;

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

		//Don't include _
		string firstVar = trim(pattern[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket-1),whitespace);
		cout << pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma - 1) << '\n';
		string second = removeSpaces(pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma-1),whitespace);
		int flag = (second.find("_") != -1);
		int flag2 = (second.length() > 1);
		if (flag && flag2) {
			while (second.find("_") != -1) {
				int index = second.find("_");
				second = second.erase(index, index + 1);
			}
		}
		cout << second << '\n';
		second = removeWhiteSpaces(second, whitespacech);
		//Check if the second parameter is just "_"
		second.erase(remove_if(second.begin(), second.end(), isspace), second.end());
		string secondVar = second;
		if (!(second.size() == 1 && second.at(0) == '_')) {
			secondVar = infixtoRPNexpression(second);
		}
		//string secondVar = infixtoRPNexpression(second);
		cout << secondVar << '\n';

		if (flag && flag2) {
			secondVar.insert(0,"_");
			secondVar.insert(secondVar.length(),"_");
			cout << secondVar << '\n';
		}

		s.push_back(make_pair(clauseType, make_pair(firstVar, secondVar)));
	}

	return s;
}

//Split by brackets
//list<string> QueryParser::evalQuery(Query q) {
//	return Evaluator::evalQuery(q) ;
//}

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

	//Select is at the start of the query, no declarations
	else if (query.find("Select") == 0) {
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
	if (declerationVariables.empty()) {
		resultString = "Invalid";
		return resultString;
	}
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

string QueryParser::selectVariablesValidation(unordered_map<string, string> declerationVariables, string selectVars) {

	string resultString = "Okay";

	//No variables to select
	if (selectVars.empty()) {
		resultString = "Invalid";
		return resultString;
	}

	if (declerationVariables.find(selectVars) == declerationVariables.end()) {
		resultString = "Invalid";
		return resultString;
	}

	//First character not alphabet
	else if (!isalpha(selectVars[0])) {
		resultString = "Invalid";
		return resultString;
	}

	//Rest must be alphabets or numbers
	for (int j = 1; j < selectVars.length(); j++) {
		if (!isalnum(selectVars[j])) {
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

			else if (isdigit(suchThat[0].second.first[0])) {
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

			else if (isdigit(suchThat[0].second.second[0])) {
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
		else if (suchThat[i].first == "Follows" || suchThat[i].first == "Follows*" || suchThat[i].first == "Next" || suchThat[i].first == "Next*") {

			// Validating first args
			if (suchThat[i].second.first == "_" || validArgs.find(firstArgsType) != validArgs.end()) {
				// valid first args
			}

			else if (isdigit(suchThat[0].second.first[0])) {
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

			else if (isdigit(suchThat[0].second.second[0])) {
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

			if (isdigit(suchThat[0].second.first[0])) {
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

			else if (isdigit(suchThat[0].second.second[0])) {
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

			if (isdigit(suchThat[0].second.first[0])) {
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

			else if (isdigit(suchThat[0].second.second[0])) {
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
	}
	return resultString;
}

//Helper method to split string
template <typename Out>
void split(const std::string& s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

string QueryParser::infixtoRPNexpression(string infix) {
	string newString = "";
	int pos = 0;
	for (char& c : infix) {
		string s(1, c);
		string tempStr = s;
		if (!isalpha(c) && !isdigit(c)) {
			
			tempStr = " " + s + " ";
		}
		newString.append(tempStr);
	}
	vector<string> vectorString = split(newString, ' ');
	int precedenceWeight;
	string rpnExpression = "";
	stack<string> workingStack;
	for (int i = 0; i < vectorString.size(); i++) {
		string tempStr = vectorString[i];
		if (tempStr == "") {
			continue;
		}
		//If is (, push to stack
		if (tempStr == "(") {
			workingStack.push(tempStr);
			continue;
		}

		//If is ), pop tokens from stack and append to output until ( is seen, then pop (
		if (tempStr == ")") {
			while (!workingStack.empty() && workingStack.top() != "(") {
				rpnExpression.append(workingStack.top());
				workingStack.pop();

			}
			if (!workingStack.empty()) {
				workingStack.pop();
			}
			continue;
		}

		precedenceWeight = getPrecedenceWeight(tempStr);
		//If is number, append to output
		if (precedenceWeight == 1) {

				rpnExpression.append("_");
				rpnExpression.append(tempStr);
				rpnExpression.append("_");
			
		}
		else {
			if (workingStack.empty()) {
				workingStack.push(tempStr);
			}
			else {
				//If operator on the top of stack has greater precedence, pop the operator and append to output
				//Brackets don't count
				while (!workingStack.empty() && (workingStack.top() != "(") && precedenceWeight <= getPrecedenceWeight(workingStack.top())) {
					rpnExpression.append(workingStack.top());
					workingStack.pop();
				}

				//Push current operator to stack
				workingStack.push(tempStr);
			}
		}
	}
	//Once above is done, if there's tokens in the stack, append to output
	while (!workingStack.empty())
	{
		rpnExpression.append(workingStack.top());
		workingStack.pop();
	}
	/*
	stack<char> workingStack;
	int i = 0;
	int j = 0;
	int precedenceWeight;
	string rpnExpression = "";
	size_t  positionOperant = 0;
	int wordSize = 0;
	
	


	while (i < infix.size()) {
		char tempStr = infix[i];
		bool isOperatorFlag = false;

		
		if (infix.size() == 1) {
			positionOperant = i;
			isOperatorFlag = true;
		}
		//check if previous char is an operator
		if (i > 0 && !isalpha(infix[i - 1]) && !isdigit(infix[i - 1])) {
			positionOperant = i;
			//wordSize = i - wordSize + 1;
		}
		
		if (i == infix.size() - 1) {
			isOperatorFlag = true;
		}
		if (i + 1 < infix.size()) {
			if(!isalpha(infix[i + 1]) && !isdigit(infix[i + 1])) {
				isOperatorFlag = true;
			}
		}
		

		//If is (, push to stack
		if (infix[i] == '(') {
			workingStack.push(tempStr);
			i++;
			continue;
		}

		//If is ), pop tokens from stack and append to output until ( is seen, then pop (
		if (tempStr == ')') {
			while (!workingStack.empty() && workingStack.top() != '(') {
				rpnExpression.append(1,workingStack.top());
				workingStack.pop();

			}
			if (!workingStack.empty()) {
				workingStack.pop();
			}
			i++;
			continue;
		}

		precedenceWeight = getPrecedenceWeight(tempStr);
		//If is number, append to output
		if (precedenceWeight == 1) {
			if (!isOperatorFlag) {
				rpnExpression.append(1, tempStr);
			}
			else {
				//rpnExpression.insert(i,"_");
				rpnExpression.append(1, tempStr);
				rpnExpression.append("_");
			}
		}
		else {
			if (workingStack.empty()) {
				workingStack.push(tempStr);
			}
			else {
				//If operator on the top of stack has greater precedence, pop the operator and append to output
				//Brackets don't count
				while (!workingStack.empty() && (workingStack.top() != '(') && precedenceWeight <= getPrecedenceWeight(workingStack.top())) {
					rpnExpression.append(1,workingStack.top());
					workingStack.pop();
				}

				//Push current operator to stack
				workingStack.push(tempStr);
			}
		}
		i++;
	}*/
	
	
	return rpnExpression;
}

int QueryParser::getPrecedenceWeight(string token) {
	if (token == "*" || token == "/" || token == "%") {
		return 3;
	}

	else if (token == "+" || token == "-") {
		return 2;
	}

	else {
		return 1;
	}
}