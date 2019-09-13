#include "TestWrapper.h"
#include "Parser.h"
#include "PKB.h"
#include "Evaluator.h"
#include "QueryParser.h"

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
	parser.Parse(filename);
  // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
	QueryParser queryParser = QueryParser();
	std::string evResult = queryParser.parse(query);

	//std::cout << evResult;


  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.

	results.push_front(evResult);	

}
