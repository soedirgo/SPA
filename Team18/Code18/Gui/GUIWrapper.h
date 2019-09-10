#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

#include"../source/PKB.h"
#include"../source/Parser.h"

class GUIWrapper {
	public:
	Parser parser;
	PKB mainPKB;
	// default constructor
	GUIWrapper();
  
	// destructor
	~GUIWrapper();
  
	// method for parsing the SIMPLE source
	virtual void parse(std::string filename);
  
	// method for evaluating a query
	virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
