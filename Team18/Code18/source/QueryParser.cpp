using namespace std;

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "Evaluator.h"
#include "Query.h"
#include "QueryParser.h"

string whitespace = " \n\t";
string QueryParser::parse(string query) {
	vector<string> statements = findInitialDecleration(query);

	unordered_map<string, string> declerationVariables = splitVariablesInDeclerations(statements);

	string select = statements[statements.size() - 1];

	vector<string> selectVars;
	vector<pair<string, pair<string, string>>> suchThat;
	vector<string> suchThatClauses;

	//Finds the first occurance of such that in the string
	int suchThatIndex = select.find("such that ");

	//Only have select variables
	if (suchThatIndex == -1) {
		selectVars = splitSelect(select);
	}

	//Split the word select out and remove it away from the select string
	else {
		selectVars = splitSelect(select.substr(0, suchThatIndex));
		select = select.substr(suchThatIndex);
	}

	//Find the next occurance of such that, push it to SuchThatClauses. Continues till no more select statements
	while (select.length() > 0) {
		suchThatIndex = select.substr(1).find(" such that");
		string currentClause = select.substr(0, suchThatIndex);
		if (currentClause.find("such that ")) {
			suchThatClauses.push_back(currentClause);
		}

		select = select.substr(suchThatIndex);
	}

	suchThat = splitSuchThat(suchThatClauses);
	
	Query q = Query(declerationVariables, selectVars, suchThat);
	string finalOutput = evalQuery(q);
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
vector<string> QueryParser::splitSelect(string statements) {
	vector<string> s;
	int firstSpace = statements.find_first_of(whitespace);
	string variableName;
	int pos;

	if (firstSpace != -1) {
		variableName = removeSpaces(statements.substr(firstSpace), whitespace);
	}

	if (variableName.find("<") != -1 && variableName.find(">") != -1) {
		variableName = variableName.substr(1, variableName.length() - 2);

		while (variableName.find(",") != -1) {
			pos = variableName.find(",");
			s.push_back(variableName.substr(0, pos));
			variableName = variableName.substr(pos + 1);
		}
	}

	s.push_back(variableName);

	return s;
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
string QueryParser::evalQuery(Query q) {
	string s = "";
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