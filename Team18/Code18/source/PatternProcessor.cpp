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
                rpnExpression += " ";
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

		}
		else {
			if (workingStack.empty()) {
				workingStack.push(tempStr);
			}
			else {
				//If operator on the top of stack has greater precedence, pop the operator and append to output
				//Brackets don't count
				while (!workingStack.empty() && (workingStack.top() != "(") && precedenceWeight <= getPrecedenceWeight(workingStack.top())) {
                    rpnExpression.append(" ");
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
        rpnExpression.append(" ");
		rpnExpression.append(workingStack.top());
		workingStack.pop();
	}
    if (rpnExpression.size())
        rpnExpression.append(" ");


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