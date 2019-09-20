using namespace std;

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

#include "Evaluator.h"
#include "Query.h"
#include "QueryParser.h"

string whitespace = " ";
unordered_set<string> validTypes = { "stmt", "variable", "assign", "constant", "read", "while", "if",
"print", "procedure" };
int maxInt = numeric_limits<int>::max();

list<string> QueryParser::parse(string query) {

	list<string> finalOutput;
	
	//Empty query
	if (query.empty()) {
		finalOutput.push_back("Invalid");
		return finalOutput;
	}

	//Select is at the start of the query, no declarations
	else if (query.find("Select") == 0) {
		finalOutput.push_back("None");
		return finalOutput;
	}

	vector<string> statements = findInitialDecleration(query);

	unordered_map<string, string> declerationVariables = splitVariablesInDeclerations(statements);
	
	//Iterate through the map of declaration variables and see if there's anything invalid
	for (auto iterator : declerationVariables) {
		if (validTypes.find(iterator.second) == validTypes.end()) {
			finalOutput.push_back("Invalid");
			return finalOutput;
		}

		if (iterator.first.empty()) {
			finalOutput.push_back("Invalid");
			return finalOutput;
		}
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

	//Find the next occurance of such that, push it to SuchThatClauses/PatternClauses. Continues till no more select statements
	while (select.length() > 0 && currentIndex != -1) {
		suchThatIndex = select.substr(1).find(" such that");
		patternIndex = select.substr(1).find(" pattern ");
		indexes = { suchThatIndex, patternIndex,};
		currentIndex = getMinimumIndex(indexes) + 1;

		if (currentIndex == 0) {
			currentIndex = select.length();
		}

		else {
			currentIndex = currentIndex + 1;
		}

		string currentClause = select.substr(0, suchThatIndex);
		if (currentClause.find("such that ") != -1) {
			suchThatClauses.push_back(currentClause);
		}

		else if (currentClause.find("pattern ") != -1) {
			patternClauses.push_back(currentClause);
		}
		
		select = select.substr(currentIndex);
	}

	suchThat = splitSuchThat(suchThatClauses);
	pattern = splitPattern(patternClauses);

	Query q = Query(declerationVariables, selectVars, suchThat, pattern);
	finalOutput = evalQuery(q);
	
	return finalOutput;
	
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
			//trim out a
			clauseType = trim(pattern[i].substr(7, posOfOpenBracket - 7), whitespace);
		}
		else {
			clauseType = trim(pattern[i].substr(3, posOfOpenBracket - 3), whitespace);
		}

		//Don't include _
		string firstVar = trim(pattern[i].substr(posOfOpenBracket + 1, posOfComma - posOfOpenBracket-1),whitespace);
		string secondVar = removeSpaces(pattern[i].substr(posOfComma + 1, posOfCloseBracket - posOfComma-1),whitespace);
		s.push_back(make_pair(clauseType, make_pair(firstVar, secondVar)));
	}

	return s;
}

//Split by brackets
list<string> QueryParser::evalQuery(Query q) {
	return Evaluator::evalQuery(q) ;
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
