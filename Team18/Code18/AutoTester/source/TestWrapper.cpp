#include "TestWrapper.h"
#include "Parser.h"
#include "PKB.h"
#include "Evaluator.h"
#include "QueryParser.h"
#include "DesignExtractor.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
	
	
	PKB pkb;
	DesignExtractor designExtractor;
	Parser ps;
	QueryParser qps;
	//Evaluator ev;
	

}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {

	PKB pkb = PKB();
	pkb.clear();

	// call your parser to do the parsing
	Parser parser = Parser();
	try {
		parser.Parse(filename);
	}
	catch (int e) {
		cout << "Error at line: " << e;
	}

	DesignExtractor designExtractor = DesignExtractor();
	designExtractor.extractDesign();
  // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
    //if (!Preprocessor::isValid(query)) {
        //results = {};
        //return;
    //}

	PKB::clearTempPKB();
	//DesignExtractor::clearCache();
	QueryParser queryParser = QueryParser();
	Query queryObject = queryParser.parse(query);
	if (queryObject.getSelectSynonyms()[0] == "Invalid") {
		results = {};
		return;
	}

	if (queryObject.getSelectSynonyms()[0] == "Semantic Invalid") {
		results = { "FALSE" };
		return;
	}
	//Clears Next*, Affects, Affects* PKB Temp Tables
	//PKB::clearTempPKB();
	results = Evaluator::evaluate(queryObject);
	

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.

	//results = evResult;	

}
