#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBNext.h"
#include "PKBAffects.h"
#include "PKB.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBAffectsTest)
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
				16.		z = x;
				17.		v = z;
				18.		print v; }
		   */
			PKB PKB;
			PKB.clear();
			PKB.setStmt("1", "read");
			PKB.setStmt("2", "read");
			PKB.setStmt("3", "call");
			PKB.setStmt("4", "assign");
			PKB.setStmt("5", "assign");
			PKB.setStmt("6", "while");
			PKB.setStmt("7", "assign");
			PKB.setStmt("8", "call");
			PKB.setStmt("9", "assign");
			PKB.setStmt("10", "if");
			PKB.setStmt("11", "assign");
			PKB.setStmt("12", "assign");
			PKB.setStmt("13", "assign");
			PKB.setStmt("14", "assign");
			PKB.setStmt("15", "assign");
			PKB.setStmt("16", "assign");
			PKB.setStmt("17", "assign");
			PKB.setStmt("18", "print");

			PKB.setFollows("1", "2");
			PKB.setFollows("2", "3");
			PKB.setFollows("4", "5");
			PKB.setFollows("5", "6");
			PKB.setFollows("6", "10");
			PKB.setFollows("10", "13");
			PKB.setFollows("7", "8");
			PKB.setFollows("8", "9");
			PKB.setFollows("13", "14");
			PKB.setFollows("14", "15");
			PKB.setFollows("16", "17");
			PKB.setFollows("17", "18");

			PKB.setNext("1", "2");
			PKB.setNext("2", "3");
			PKB.setNext("4", "5");
			PKB.setNext("5", "6");
			PKB.setNext("6", "7");
			PKB.setNext("7", "8");
			PKB.setNext("8", "9");
			PKB.setNext("9", "6");
			PKB.setNext("6", "10");
			PKB.setNext("10", "11");
			PKB.setNext("10", "12");
			PKB.setNext("11", "13");
			PKB.setNext("12", "13");
			PKB.setNext("13", "14");
			PKB.setNext("14", "15");
			PKB.setNext("16", "17");
			PKB.setNext("17", "18");

			PKB.setCallProc("First", "Second");
			PKB.setCallProc("Second", "Third");

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
			PKB.setModifiesS("8", "z");
			PKB.setModifiesS("8", "v");
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

			//Line #3 Calls Second
			PKB.setUsesS("3", "y");
			PKB.setUsesS("3", "i");
			PKB.setUsesS("3", "x");
			PKB.setUsesS("3", "z");
			PKB.setUsesS("3", "v"); //#3 Calls Second, which calls Third

			//Direct assignment stmts with var on RHS 
			PKB.setUsesS("6", "i");
			PKB.setUsesS("7", "x");
			PKB.setUsesS("7", "y");
			PKB.setUsesS("9", "i");
			PKB.setUsesS("6", "x");
			PKB.setUsesS("6", "y");
			PKB.setUsesS("6", "i");
			PKB.setUsesS("8", "z");
			PKB.setUsesS("8", "v");
			PKB.setUsesS("10", "x");
			PKB.setUsesS("11", "x");
			PKB.setUsesS("13", "z");
			PKB.setUsesS("13", "x");
			PKB.setUsesS("13", "i");
			PKB.setUsesS("14", "z");
			PKB.setUsesS("15", "x");
			PKB.setUsesS("15", "y");
			PKB.setUsesS("15", "z");
			PKB.setUsesS("16", "x");
			PKB.setUsesS("17", "z");
			PKB.setUsesS("18", "v");

			//More complex uses 
			PKB.setUsesP("Second", "i");
			PKB.setUsesP("Second", "x");
			PKB.setUsesP("Second", "y");
			PKB.setUsesP("Second", "z");
			PKB.setUsesP("Third", "x");
			PKB.setUsesP("Third", "z");

			PKB.setProcedure("First", "1", { {"2"} });
			PKB.setProcedure("Second", "4", { {"11","15"} });
			PKB.setProcedure("Third", "16", { {"18"} });

			PKB.setCallStmt("3", "Second");
			PKB.setCallStmt("8", "Third");

			PKB.setCallProc("First", "Second");
			PKB.setCallProc("Second", "Third");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}
		//Affects(_ , _)
		TEST_METHOD(isAffectsAnyAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsAnyAny());
		}
		//Affects(_ , 7)
		TEST_METHOD(isAffectsAnyIdent)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsAnyIdent("7"));
			Assert::IsTrue(PKB.isAffectsAnyIdent("11"));
			Assert::IsTrue(PKB.isAffectsAnyIdent("13"));
			Assert::IsTrue(PKB.isAffectsAnyIdent("15"));
			Assert::IsTrue(PKB.isAffectsAnyIdent("9"));
			Assert::IsTrue(PKB.isAffectsAnyIdent("14"));
		}
		//Affects(4 , _)
		TEST_METHOD(isAffectsIdentAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsIdentAny("4"));
			Assert::IsTrue(PKB.isAffectsIdentAny("5"));
			Assert::IsTrue(PKB.isAffectsIdentAny("7"));
			Assert::IsTrue(PKB.isAffectsIdentAny("9"));
			Assert::IsTrue(PKB.isAffectsIdentAny("12"));
			Assert::IsTrue(PKB.isAffectsIdentAny("13"));
			Assert::IsTrue(PKB.isAffectsIdentAny("14"));

		}
		//Affects(4,7)
		TEST_METHOD(isAffectsIdentIdent)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsIdentIdent("4", "7"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("4", "11"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("4", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("4", "15"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("5", "9"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("5", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("7", "7"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("7", "11"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("7", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("7", "15"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("9", "9"));	
			Assert::IsTrue(PKB.isAffectsIdentIdent("9", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("11", "15"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("14", "15"));
		}

		//Affects(_,a2)
		TEST_METHOD(getAffectsAnyEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsAnyEnt();
			expected = { {"7"},{"11"},{"13"},{"15"},{"9"},{"14"},{"17"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects(a1,_)
		TEST_METHOD(getAffectsEntAny)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsEntAny();
			expected = { {"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"16"} };
			Assert::IsTrue(actual == expected);
		}

		//Affects(a1,a2)
		TEST_METHOD(getAffectsEntEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsEntEnt();
			expected = { {"4","7"},{"4","11"},{"4","13"},{"4","15"},{"5","9"},{"5","13"},{"7","7"},{"7","11"},{"7","13"},{"7","15"},{"9","9"},{"9","13"}
			,{"11","13"},{"11","15"},{"12","13"},{"13","14"},{"13","15"},{"14","15"},{"16","17"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects(a,2)
		TEST_METHOD(getAffectsEntIdent)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsEntIdent("7");
			expected = { {"4"},{"7"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects(1,a)
		TEST_METHOD(getAffectsIdentEnt)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsIdentEnt("4");
			expected = { {"7"},{"11"},{"13"},{"15"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects(a,a)
		TEST_METHOD(getAffectsSelf)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsSelf();
			expected = { {"7"} ,{"9"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects*(_ , _)
		TEST_METHOD(isAffectsTAnyAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsTAnyAny());
		}
		//Affects*(_ , 7)
		TEST_METHOD(isAffectsTAnyIdent)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsTAnyIdent("7"));
			Assert::IsTrue(PKB.isAffectsTAnyIdent("11"));
			Assert::IsTrue(PKB.isAffectsTAnyIdent("13"));
			Assert::IsTrue(PKB.isAffectsTAnyIdent("15"));
			Assert::IsTrue(PKB.isAffectsTAnyIdent("9"));
			Assert::IsTrue(PKB.isAffectsTAnyIdent("14"));
		}
		//Affects*(4 , _)
		TEST_METHOD(isAffectsTIdentAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsTIdentAny("4"));
			Assert::IsTrue(PKB.isAffectsTIdentAny("5"));
			Assert::IsTrue(PKB.isAffectsTIdentAny("7"));
			Assert::IsTrue(PKB.isAffectsTIdentAny("9"));
			Assert::IsTrue(PKB.isAffectsTIdentAny("12"));
			Assert::IsTrue(PKB.isAffectsTIdentAny("13"));
			Assert::IsTrue(PKB.isAffectsTIdentAny("14"));

		}
		//Affects*(4 , 7)
		TEST_METHOD(AffectsTRelationship)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsTIdentIdent("4", "7"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("4", "11"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("4", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("4", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("5", "9"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("5", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("7", "7"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("7", "11"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("7", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("7", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("9", "9"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("9", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("11", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("4", "14"));
		}
		//Affects*(_,a2)
		TEST_METHOD(getAffectsTAnyEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsTAnyEnt();
			expected = { {"7"},{"11"},{"13"},{"15"},{"9"},{"14"},{"17"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects*(a1,_)
		TEST_METHOD(getAffectsTEntAny)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsTEntAny();
			expected = { {"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"16"} };
			Assert::IsTrue(actual == expected);
		}

		//Affects*(a1,a2)
		TEST_METHOD(getAffectsTEntEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsTEntEnt();
			expected = { {"4","7"},{"4","11"},{"4","13"},{"4","14"},{"4","15"},{"5","9"},{"5","13"},{"5","14"},{"5","15"},{"7","7"},{"7","11"},{"7","13"},{"7","14"},{"7","15"}
			,{"9","9"},{"9","13"},{"9","14"},{"9","15"},{"11","13"},{"11","14"},{"11","15"},{"12","13"},{"12","14"},{"12","15"},{"13","14"},{"13","15"},{"14","15"},{"16","17"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects*(a,2)
		TEST_METHOD(getAffectsTEntIdent)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsTEntIdent("7");
			expected = { {"4"},{"7"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects*(1,a)
		TEST_METHOD(getAffectsTIdentEnt)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsTIdentEnt("4");
			expected = { {"7"},{"11"},{"13"},{"14"},{"15"} };
			Assert::IsTrue(actual == expected);
		}
		//Affects*(a,a)
		TEST_METHOD(getAffectsTSelf)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsTSelf();
			expected = { {"7"},{"9"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip(_ , _)
		TEST_METHOD(isAffectsBipAnyAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipAnyAny());
		}
		//AffectsBip(_ , 7)
		TEST_METHOD(isAffectsBipAnyIdent)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipAnyIdent("7"));
			Assert::IsTrue(PKB.isAffectsBipAnyIdent("11"));
			Assert::IsTrue(PKB.isAffectsBipAnyIdent("13"));
			Assert::IsTrue(PKB.isAffectsBipAnyIdent("15"));
			Assert::IsTrue(PKB.isAffectsBipAnyIdent("9"));
			Assert::IsTrue(PKB.isAffectsBipAnyIdent("14"));
		}
		//AffectsBip(4 , _)
		TEST_METHOD(isAffectsBipIdentAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipIdentAny("4"));
			Assert::IsTrue(PKB.isAffectsBipIdentAny("5"));
			Assert::IsTrue(PKB.isAffectsBipIdentAny("7"));
			Assert::IsTrue(PKB.isAffectsBipIdentAny("9"));
			Assert::IsTrue(PKB.isAffectsBipIdentAny("12"));
			Assert::IsTrue(PKB.isAffectsBipIdentAny("13"));
			Assert::IsTrue(PKB.isAffectsBipIdentAny("14"));

		}
		//AffectsBip(4,7)
		TEST_METHOD(isAffectsBipIdentIdent)
		{
			DesignExtractor ds;
			ds.extractDesign();
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("4", "7"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("4", "11"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("4", "13"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("4", "15"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("5", "9"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("5", "13"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("7", "7"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("7", "11"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("7", "13"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("7", "15"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("9", "9"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("9", "13"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("11", "15"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isAffectsBipIdentIdent("7", "16"));
		}

		//AffectsBip(_,a2)
		TEST_METHOD(getAffectsBipAnyEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsBipAnyEnt();
			expected = { {"7"},{"11"},{"13"},{"15"},{"9"},{"14"},{"16"},{"17"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip(a1,_)
		TEST_METHOD(getAffectsBipEntAny)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsBipEntAny();
			expected = { {"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"16"} };
			Assert::IsTrue(actual == expected);
		}

		//AffectsBip(a1,a2)
		TEST_METHOD(getAffectsBipEntEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsBipEntEnt();
			expected = { {"4","7"},{"4","11"},{"4","13"},{"4","15"},{"5","9"},{"5","13"},{"7","7"},{"7","11"},{"7","13"},{"7","15"},{"9","9"},{"9","13"}
			,{"11","13"},{"11","15"},{"12","13"},{"13","14"},{"13","15"},{"14","15"},{"16","17"},{"7","16"},{"16","13"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip(a,2)
		TEST_METHOD(getAffectsBipEntIdent)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsBipEntIdent("7");
			expected = { {"4"},{"7"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip(1,a)
		TEST_METHOD(getAffectsBipIdentEnt)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsBipIdentEnt("4");
			expected = { {"7"},{"11"},{"13"},{"15"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip(a,a)
		TEST_METHOD(getAffectsBipSelf)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsBipSelf();
			expected = { {"7"} ,{"9"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip*(_ , _)
		TEST_METHOD(isAffectsBipTAnyAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipTAnyAny());
		}
		//AffectsBip*(_ , 7)
		TEST_METHOD(isAffectsBipTAnyIdent)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipTAnyIdent("7"));
			Assert::IsTrue(PKB.isAffectsBipTAnyIdent("11"));
			Assert::IsTrue(PKB.isAffectsBipTAnyIdent("13"));
			Assert::IsTrue(PKB.isAffectsBipTAnyIdent("15"));
			Assert::IsTrue(PKB.isAffectsBipTAnyIdent("9"));
			Assert::IsTrue(PKB.isAffectsBipTAnyIdent("14"));
		}
		//AffectsBip*(4 , _)
		TEST_METHOD(isAffectsBipTIdentAny)
		{
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("4"));
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("5"));
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("7"));
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("9"));
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("12"));
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentAny("14"));

		}
		//AffectsBip*(4,7)
		TEST_METHOD(isAffectsBipTIdentIdent)
		{
			DesignExtractor ds;
			ds.extractDesign();
			PKBAffects PKB;
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("4", "7"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("4", "11"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("4", "13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("4", "15"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("5", "9"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("5", "13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("7", "7"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("7", "11"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("7", "13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("7", "15"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("9", "9"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("9", "13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("11", "15"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isAffectsBipTIdentIdent("7", "16"));
		}

		//AffectsBip*(_,a2)
		TEST_METHOD(getAffectsBipTAnyEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsBipTAnyEnt();
			expected = { {"7"},{"11"},{"13"},{"15"},{"9"},{"14"},{"16"},{"17"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip*(a1,_)
		TEST_METHOD(getAffectsBipTEntAny)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsBipTEntAny();
			expected = { {"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"16"} };
			Assert::IsTrue(actual == expected);
		}

		//AffectsBip*(a1,a2)
		TEST_METHOD(getAffectsBipTEntEnt)
		{
			PKBAffects PKB;
			TABLE actual, expected;

			actual = PKB.getAffectsBipTEntEnt();
			expected = { {"4","7"},{"4","11"},{"4","13"},{"4","14"},{"4","15"},{"4","16"},{"4","17"},{"5","9"},{"5","13"},{"5","14"},{"5","15"},{"7","7"},{"7","11"},{"7","13"},{"7","14"}
				,{"7","15"},{"7","16"},{"7","17"},{"9","9"},{"9","13"},{"9","14"},{"9","15"},{"11","13"},{"11","14"},{"11","15"},{"12","13"},{"12","14"},{"12","15"},{"13","14"},{"13","15"}
			,{"14","15"},{"16","13"},{"16","17"},{"16","14"} ,{"16","15"}};
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip*(a,2)
		TEST_METHOD(getAffectsBipTEntIdent)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsBipTEntIdent("7");
			expected = { {"4"},{"7"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip*(1,a)
		TEST_METHOD(getAffectsBipTIdentEnt)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsBipTIdentEnt("4");
			expected = { {"7"},{"11"},{"13"},{"14"}, {"15"},{"17"},{"16"} };
			Assert::IsTrue(actual == expected);
		}
		//AffectsBip*(a,a)
		TEST_METHOD(getAffectsBipTSelf)
		{
			PKBAffects PKB;
			LINE_LIST actual, expected;

			actual = PKB.getAffectsBipTSelf();
			expected = { {"7"} ,{"9"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


