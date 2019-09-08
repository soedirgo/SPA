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

	//Query q = Query(declerationVariables, selectVars, suchThat);
	//string finalOutput = evalQuery(q);
	//return finalOutput;
	string s = "";
	return s;
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

//
unordered_map<string, string> QueryParser::splitVariablesInDeclerations(vector<string> declerations) {
	unordered_map<string, string> taggedDeclerationVariables;
	int declerationsSize = declerations.size();
	int i;
	for (i = 0; i < declerationsSize - 1; i++) {
		string currentDeclerations = declerations[i];
		int charSpaceLoc = currentDeclerations.find_first_of(whitespace);
		string type = currentDeclerations.substr(0, charSpaceLoc);
		string varName = currentDeclerations.substr(charSpaceLoc);

		if (varName.find(",") != -1) {
			char delimiter = ',';
			int start = 0;
			int end = varName.find(delimiter);

			while (end != -1) {
				string varNameSplitted = trim(varName.substr(start, end - start), whitespace);
				taggedDeclerationVariables.insert(make_pair(varNameSplitted, type));
				start = end + 1;
				end = varName.find(delimiter, start);
			}

			taggedDeclerationVariables.insert(make_pair(trim(varName.substr(start), whitespace), type));
		}
		else {
			taggedDeclerationVariables.insert(make_pair(trim(varName, whitespace), type));
		}
	}

	return taggedDeclerationVariables;
}

//Split by whitespace
vector<string> QueryParser::splitSelect(string statements) {
	vector<string> s;
	int firstSpace = statements.find_first_of(whitespace);
	string varName;

	if (firstSpace != -1) {
		varName = removeSpaces(statements.substr(firstSpace), whitespace);
	}

	if (varName.find("<") != -1 && varName.find(">") != -1) {
		varName = varName.substr(1, varName.length() - 2);

		while (varName.find(",") != -1) {
			int delimiterComma = varName.find(",");
			s.push_back(varName.substr(0, delimiterComma));
			varName = varName.substr(delimiterComma + 1);
		}
	}

	s.push_back(varName);

	return s;
}


//Split by brackets
vector<pair<string, pair<string, string>>> QueryParser::splitSuchThat(vector<string> suchThat) {
	vector<pair<string, pair<string, string>>> s;
	int i = 0;

	for (i = 0; i < suchThat.size(); i++) {
		int openBracket = suchThat[i].find("(");
		int comma = suchThat[i].find(",");
		int closeBracket = suchThat[i].find(")");
		int strLen = suchThat[i].length();
		string condition;

		if (openBracket == -1 || comma == -1 || closeBracket == -1) {
			s.push_back(make_pair("", make_pair("", "")));
			continue;
		}

		if (suchThat[i].find("such") != -1) {
			condition = removeSpaces(suchThat[i].substr(9, openBracket - 9), whitespace);
		}
		else {
			condition = removeSpaces(suchThat[i].substr(3, openBracket - 3), whitespace);
		}

		string firstVar;
		string secondVar;

		if ((comma - openBracket - 1) < 0) {
			firstVar = "";
		}
		else {
			firstVar = removeSpaces(suchThat[i].substr(openBracket + 1, comma - openBracket - 1), whitespace);
		}

		if ((closeBracket - comma - 1) < 0) {
			secondVar = "";
		}
		else {
			secondVar = removeSpaces(suchThat[i].substr(comma + 1, closeBracket - comma - 1), whitespace);
		}

		s.push_back(make_pair(condition, make_pair(firstVar, secondVar)));
	}

	return s;
}

//Split by brackets
//string QueryParser::evalQuery(Query q) {
//	return Evaluator::evalQuery(q);
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

//Splits the string based on the given limiter and returns a vector of substrings.
/*
vector<string> splitString(string statement, char delimiter) {
	vector<string> stringVector;
	string::size_type i = 0;
	string::size_type j = statement.find(delimiter);

	//Parse statements until it's end of string
	while (j != string::npos) {
		//Push result into vector.
		stringVector.push_back(statement.substr(i, j - i));
		//Update i after the delimiter position j
		j = j + 1;
		i = j;
		//Get the new position for delimiter
		j = statement.find(delimiter, j);
	}

	if (j == string::npos)
		stringVector.push_back(statement.substr(i, statement.length()));

	return stringVector;
}
*/

//Removes all the whitespace in the given string
string QueryParser::removeSpaces(string s, string whitespace) {
	s.erase(0, s.find_first_not_of(whitespace));
	s.erase(s.find_last_not_of(whitespace) + 1);
	return s;
}