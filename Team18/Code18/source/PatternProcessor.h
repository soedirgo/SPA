#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <stack>

class PatternProcessor {
public:
	
	static std::string infixtoRPNexpression(std::string infix);
	static int getPrecedenceWeight(std::string token);
};