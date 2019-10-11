#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBModifies.h"
#include "DesignExtractor.h"
#include "PKBStmt.h"
#include "PKBCall.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBModifiesTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**	SIMPLE program:

				procedure First {
				1.	read x;
				2.	read z;
				3.	call Second; }

				procedure Second {
				4.		x = 0;
				5.		i = 5;
				6.		while (i!=0) {
				7.			x = x + 2*y;
				8.			call Third;
				9.			i = i - 1; }
				10.		if (x==1) then {
				11.			x = x+1; }
						else {
				12.			z = 1; }
				13.		z = z + x + i;
				14.		y = z + 2;
				15.		x = x * y + z; }

					procedure Third {
				16.		z = 5;
				17.		v = z;
				18.		print v; }
		   */

			PKB PKB;
			PKBStmt Stmts;
			PKBCall Calls;
			PKB.clear();

			Stmts.setStmt("1", "read");
			Stmts.setStmt("2", "read");
			Stmts.setStmt("3", "call");
			Stmts.setStmt("4", "assign");
			Stmts.setStmt("5", "assign");
			Stmts.setStmt("6", "while");
			Stmts.setStmt("7", "assign");
			Stmts.setStmt("8", "call");
			Stmts.setStmt("9", "assign");
			Stmts.setStmt("10", "if");
			Stmts.setStmt("11", "assign");
			Stmts.setStmt("12", "assign");
			Stmts.setStmt("13", "assign");
			Stmts.setStmt("14", "assign");
			Stmts.setStmt("15", "assign");
			Stmts.setStmt("16", "assign");
			Stmts.setStmt("17", "assign");
			Stmts.setStmt("18", "print");


			//Procedure First
			PKB.setModifiesS("1", "x");
			PKB.setModifiesS("2", "z");
			PKB.setModifiesS("3", "x");
			PKB.setModifiesS("3", "i");
			PKB.setModifiesS("3", "y");
			PKB.setModifiesS("3", "z");
			PKB.setModifiesS("3", "v");

			//Procedure Second
			PKB.setModifiesS("4", "x");
			PKB.setModifiesS("5", "i");

			PKB.setModifiesS("6", "x");
			PKB.setModifiesS("6", "i");
			PKB.setModifiesS("6", "z");
			PKB.setModifiesS("6", "v");

			PKB.setModifiesS("7", "x");

			PKB.setModifiesS("8", "z") ;
			PKB.setModifiesS("8", "v") ;

			PKB.setModifiesS("9", "i");

			PKB.setModifiesS("10", "x");
			PKB.setModifiesS("10", "z");
			PKB.setModifiesS("11", "x");
			PKB.setModifiesS("12", "z");


			PKB.setModifiesS("13", "z");
			PKB.setModifiesS("14", "y");
			PKB.setModifiesS("15", "x");

			//Procedure Third 
			PKB.setModifiesS("16", "z");
			PKB.setModifiesS("17", "v");

			PKB.setModifiesP("First", "x");
			PKB.setModifiesP("First", "z");

			//Set Modifies Procedures
			PKB.setModifiesP("Second", "x");
			PKB.setModifiesP("Second", "i");
			PKB.setModifiesP("Second", "y");
			PKB.setModifiesP("Second", "z");

			PKB.setModifiesP("Third", "z");
			PKB.setModifiesP("Third", "v");

			PKB.setModifiesP("Second", "z");
			PKB.setModifiesP("Second", "v");

			PKB.setModifiesP("First", "z");
			PKB.setModifiesP("First", "v");
			PKB.setModifiesP("First", "x");
			PKB.setModifiesP("First", "i");
			PKB.setModifiesP("First", "y");
			PKB.setModifiesP("First", "z");

		}

		TEST_METHOD(isModifiesSIdentIdent)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isModifiesSIdentIdent("1", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("2", "z"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("4", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("5", "i"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("7", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("9", "i"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("11", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("12", "z"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("13", "z"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("14", "y"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("15", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("16", "z"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("17", "v"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("6", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("6", "z"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("10", "x"));
			Assert::IsTrue(PKB.isModifiesSIdentIdent("10", "z"));

		}

		TEST_METHOD(isModifiesPIdentIdent)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "x"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "z"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Second", "x"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Second", "i"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Second", "y"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Second", "z"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Third", "z"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Third", "v"));

			Assert::IsTrue(PKB.isModifiesPIdentIdent("Second", "z"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("Second", "v"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "z"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "v"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "x"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "i"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "y"));
			Assert::IsTrue(PKB.isModifiesPIdentIdent("First", "z"));

		}


		TEST_METHOD(getModifiesSEntAny)
		{//LHS is either a if/while/assign/call 
			PKBModifies PKB;
			STMT_LIST ifResult = PKB.getModifiesSEntAny("if");
			STMT_LIST ifExpected = { {"10"} };
			Assert::IsTrue(ifExpected == ifResult);

			STMT_LIST printResult = PKB.getModifiesSEntAny("read");
			STMT_LIST printExpected = { {"1"} , {"2"}  };
			Assert::IsTrue(printExpected == printResult);

			STMT_LIST assignResult = PKB.getModifiesSEntAny("assign");
			STMT_LIST assignExpected = { {"4"}, {"5"}, {"7"}, {"9"}, {"11"},{"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"} };
			Assert::IsTrue(assignExpected == assignResult);

			STMT_LIST callResult = PKB.getModifiesSEntAny("call");//Second third firs
			STMT_LIST callExpected = { {"3"}, {"8"} };
			Assert::IsTrue(callExpected == callResult);

			STMT_LIST whileResult = PKB.getModifiesSEntAny("while");
			STMT_LIST whileExpected = { {"6"} };
			Assert::IsTrue(whileExpected == whileResult);

			STMT_LIST allModifiesResults = PKB.getModifiesSEntAny("stmt");
			STMT_LIST allModifiesExpected = { {"1"} ,{"2"} ,{"3"} , {"4"} ,{"5"} ,{"6"},{"7"}, {"8"},{"9"},{"10"},{"11"},{"12"} ,{"13"},{"14"},{"15"},{"16"} ,{"17"} };
			Assert::IsTrue(allModifiesResults == allModifiesExpected);

		}

		TEST_METHOD(getModifiesSEntIdent)
		{//LHS is either a print/if/while/assign/call 
			PKBModifies PKB;
			STMT_LIST result = PKB.getModifiesSEntIdent("assign", "i");
			STMT_LIST expected = { {"5"}, {"9"} };
			Assert::IsTrue(result == expected);


			result = PKB.getModifiesSEntIdent("assign", "x");
			expected = { {"4"} , {"7"} , {"11"}   , {"15"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("assign", "y");
			expected = { {"14"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("assign", "z");
			expected = { {"12"} ,{"13"} , {"16"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("read", "x");
			expected = { {"1"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("read", "z");
			expected = { {"2"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("if", "x");
			expected = { {"10"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("if", "z");
			expected = { {"10"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("while", "i");
			expected = { {"6"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("while", "x");
			expected = { {"6"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("while", "z");
			expected = { {"6"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("while", "v");
			expected = { {"6"} };
			Assert::IsTrue(result == expected);


			result = PKB.getModifiesSEntIdent("call", "i");
			expected = { {"3"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("call", "x");
			expected = { {"3"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("call", "y");
			expected = { {"3"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("call", "z");
			expected = { {"3"} , {"8"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("call", "v");
			expected = { {"3"} , {"8"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("stmt", "v");
			expected = { {"3"} , {"6"}, {"8"} , {"17"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("stmt", "z");
			expected = { {"2"} ,{"3"} , {"6"} ,{"8"} , {"10"},  {"12"}, {"13"}, {"16"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("stmt", "x");
			expected = { {"1"} ,{"3"} , {"4"} , {"6"} ,{"7"} , {"10"}, {"11"}, {"15"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("stmt", "y");
			expected = { {"3"} , {"14"} };
			Assert::IsTrue(result == expected);

			result = PKB.getModifiesSEntIdent("stmt", "i");
			expected = { {"3"}, {"5"} , {"6"} ,{"9"}  };
			Assert::IsTrue(result == expected);


		}

		TEST_METHOD(getModifiesSIdentEnt) {
			PKBModifies pkb;

			//All empty result queries
			STMT_LIST expected = {{"x"}};
			VAR_LIST result = pkb.getModifiesSIdentEnt("1");
			result = pkb.getModifiesSIdentEnt("4");
			Assert::IsTrue(result == expected);
			result = pkb.getModifiesSIdentEnt("7");
			Assert::IsTrue(result == expected);
			result = pkb.getModifiesSIdentEnt("11");
			Assert::IsTrue(result == expected);


			Assert::IsTrue(result == expected);
			expected = { {"z"} };
			result = pkb.getModifiesSIdentEnt("2");
			Assert::IsTrue(result == expected);

			expected = { {"i"} };
			result = pkb.getModifiesSIdentEnt("5");
			Assert::IsTrue(result == expected);

			expected = { {"x"} , {"y"}, {"z"}, {"v"}, {"i"} };
			result = pkb.getModifiesSIdentEnt("3");//Special call stmt case
			Assert::IsTrue(result == expected);

			//Other assignment cases etc. 
			expected = { {"i"}, {"x"}, {"z"} , {"v"} };
			result = pkb.getModifiesSIdentEnt("6");
			Assert::IsTrue(result == expected);

			//if
			expected = { {"x"} , {"z"} };
			result = pkb.getModifiesSIdentEnt("10");
			Assert::IsTrue(result == expected);

			//assignment
			expected = { {"x"} };
			result = pkb.getModifiesSIdentEnt("15");
			Assert::IsTrue(result == expected);
		}
		TEST_METHOD(getModifiesPEntAny) {
			PKBModifies pkb;
			PROC_LIST expected = { {"First"}, {"Second"}, {"Third"} };
			PROC_LIST result = pkb.getModifiesPEntAny();
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(getModifiesSEntEnt) {
			PKBModifies pkb;
			TABLE result = pkb.getModifiesSEntEnt("if");
			TABLE expected =
			{ { {"10"} , {"x"} }
			,{ {"10"} , {"z"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesSEntEnt("while");
			expected =
			{ { {"6"} , {"i"} }
			,{ {"6"} , {"x"} }
			,{ {"6"} , {"z"} } 
			,{ {"6"} , {"v"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesSEntEnt("read");
			expected =
			{ { {"1"} , {"x"} }
			,{ {"2"} , {"z"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesSEntEnt("assign");
			expected =
			{ { {"4"} , {"x"} }
			,{ {"5"} , {"i"} }
			,{ {"7"} , {"x"} }
			,{ {"9"} , {"i"} }
			,{ {"11"} , {"x"} }
			,{ {"12"} , {"z"} }
			,{ {"13"} , {"z"} }
			,{ {"14"} , {"y"} }
			,{ {"15"} , {"x"} }
			,{ {"16"} , {"z"} }
			,{ {"17"} , {"v"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesSEntEnt("call");
			expected =
			{ { {"3"} , {"x"} }
			,{ {"3"} , {"y"} }
			,{ {"3"} , {"i"} }
			,{ {"3"} , {"z"} }
			,{ {"3"} , {"v"} }
			,{ {"8"} , {"z"}}
			,{ {"8"} , {"v"} } };

			Assert::IsTrue(result == expected);


		}
		TEST_METHOD(getModifiesPEntIdent) {
			PKBModifies pkb;
			PROC_LIST expected = { {"First"} , {"Second"}, {"Third"} };
			PROC_LIST result = pkb.getModifiesPEntIdent("z");
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesPEntIdent("v");
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesPEntIdent("x");
			expected = { {"First"} , {"Second"} };

			result = pkb.getModifiesPEntIdent("y");
			expected = { {"First"} , {"Second"} };

		}
		TEST_METHOD(getModifiesPIdentEnt) {
			PKBModifies pkb;
			PROC_LIST expected = { {"x"}, {"y"},{"z"}, {"i"}, {"v"} };
			PROC_LIST result = pkb.getModifiesPIdentEnt("First");
			Assert::IsTrue(result == expected);

			result = pkb.getModifiesPIdentEnt("Second");
			Assert::IsTrue(result == expected);

			expected = { {"z"}, {"v"} };
			result = pkb.getModifiesPIdentEnt("Third");
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(getModifiesPEntEnt) {
			PKBModifies pkb;
			TABLE expected =
			{ { {"First"} , {"x"} }
			, { {"First"} , {"y"} }
			, { {"First"} , {"z"} }
			, { {"First"} , {"i"} }
			, { {"First"} , {"v"} }
			, { {"Second"} , {"x"} }
			, { {"Second"} , {"y"} }
			, { {"Second"} , {"z"} }
			, { {"Second"} , {"i"} }
			, { {"Second"} , {"v"} }
			, { {"Third"} , {"z"} }
			, { {"Third"} , {"v"} } };

			TABLE result = pkb.getModifiesPEntEnt();
			Assert::IsTrue(result == expected);
		}
	};
};


