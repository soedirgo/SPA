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
				16.		z = 5;
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
			PKB.setUsesS("17", "z");
			PKB.setUsesS("18", "v");

			//More complex uses 
			PKB.setUsesP("Second", "i");
			PKB.setUsesP("Second", "x");
			PKB.setUsesP("Second", "y");
			PKB.setUsesP("Second", "z");
			PKB.setUsesP("Third", "v");
			PKB.setUsesP("Third", "z");
			

			
		}
		/*
		TEST_METHOD(AffectsRelationship)
		{
			
			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
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
			Assert::IsTrue(PKB.isAffectsIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isAffectsIdentIdent("16", "17"));
			
		}
		
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
			Assert::IsTrue(PKB.isAffectsTIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isAffectsTIdentIdent("16", "17"));

			Assert::IsTrue(PKB.isAffectsTIdentIdent("4", "14"));
		}
		*/
	};
};


