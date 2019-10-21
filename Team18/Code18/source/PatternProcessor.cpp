#include "PatternProcessor.h"
#include <sstream>

using namespace std;

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

string PatternProcessor::infixtoRPNexpression(string infix) {
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

			rpnExpression.append(" ");
			rpnExpression.append(tempStr);
			rpnExpression.append(" ");

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

int PatternProcessor::getPrecedenceWeight(string token) {
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