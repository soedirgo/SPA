#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBParent.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBParentTest)
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
				9.			x = 1;
				10.			if (x==1) then {
				11.				x = x +1; }
							else {
				12.				z = 2;}
				13.			i = i - 1; }
				14.		if (x==1) then {
				15.			x = x+1; }
						else {
				16.			z = 1; }
				17.		z = z + x + i;
				18.		y = z + 2;
				19.		x = x * y + z; }

					procedure Third {
				20.		z = 5;
				21.		v = z;
				22.		print v; }
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
			PKB.setStmt("14", "if");
			PKB.setStmt("15", "assign");
			PKB.setStmt("16", "assign");
			PKB.setStmt("17", "assign");
			PKB.setStmt("18", "assign");
			PKB.setStmt("19", "assign");
			PKB.setStmt("20", "assign");
			PKB.setStmt("21", "assign");
			PKB.setStmt("22", "print");

			PKB.setParent("6", "7");
			PKB.setParent("6", "8");
			PKB.setParent("6", "9");
			PKB.setParent("6", "10");
			PKB.setParent("6", "13");
			PKB.setParent("10", "11");
			PKB.setParent("10", "12");
			PKB.setParent("14", "15");
			PKB.setParent("14", "16");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}

		//Parent( _ , _)
		TEST_METHOD(isParentAnyAny)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentAnyAny());
		}
		//Parent( _ ,2)
		TEST_METHOD(isParentAnyIdent)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentAnyIdent("7"));
			Assert::IsTrue(PKB.isParentAnyIdent("8"));
			Assert::IsTrue(PKB.isParentAnyIdent("11"));
			Assert::IsTrue(PKB.isParentAnyIdent("13"));
		}
		//Paernt(1, _)
		TEST_METHOD(isParentIdentAny)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentIdentAny("6"));
			Assert::IsTrue(PKB.isParentIdentAny("10"));
			Assert::IsTrue(PKB.isParentIdentAny("14"));
			Assert::IsFalse(PKB.isParentIdentAny("5"));
		}
		//Parent(1,2)
		TEST_METHOD(isParentIdentIdent)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentIdentIdent("6","7"));
			Assert::IsTrue(PKB.isParentIdentIdent("6", "8"));
			Assert::IsTrue(PKB.isParentIdentIdent("6", "9"));
			Assert::IsTrue(PKB.isParentIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isParentIdentIdent("10", "11"));
			Assert::IsTrue(PKB.isParentIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isParentIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isParentIdentIdent("14", "16"));
		}
		

		
		//Parent(_,s2)
		TEST_METHOD(getParentAnyEnt)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getParentAnyEnt("assign");
			expected = { {"7"},{"9"},{"11"},{"12"},{"13"},{"15"}, {"16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentAnyEnt("read");
			Assert::IsTrue(actual.size() == 0);
		}
		//Parent(s1,_)
		TEST_METHOD(getParentEntAny)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getParentEntAny("while");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentEntAny("read");
			Assert::IsTrue(actual.size() == 0);
		}
		//Parent(s1,s2)
		TEST_METHOD(getParentEntEnt)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getParentEntEnt("if", "assign");
			expected = { {"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentEntEnt("assign", "read");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getParentEntEnt("if", "stmt");
			expected = { {"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentEntEnt("stmt", "stmt");
			expected = { {"6","7"},{"6","8"},{"6","9"},{"6","10"},{"6","13"},{"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);
		}

		//Parent(s,15)
		TEST_METHOD(getParentEntIdent)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getParentEntIdent("if", "15");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentEntIdent("assign", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getParentEntIdent("while", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentEntIdent("stmt", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}

		//Parent(14,s)
		TEST_METHOD(getParentIdentEnt)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getParentIdentEnt("14", "assign");
			expected = { {"15"}, {"16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentIdentEnt("2", "assign");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getParentIdentEnt("6", "if");
			expected = { {"10"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentIdentEnt("6", "stmt");
			expected = { {"7"}, {"8"}, {"9"}, {"10"},{"13"} };
			Assert::IsTrue(actual == expected);
		}
		//Parent*( _ , _)
		TEST_METHOD(isParentTAnyAny)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentTAnyAny());
		}
		//Parent*( _ ,2)
		TEST_METHOD(isParentTAnyIdent)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentTAnyIdent("7"));
			Assert::IsTrue(PKB.isParentTAnyIdent("8"));
			Assert::IsTrue(PKB.isParentTAnyIdent("11"));
			Assert::IsTrue(PKB.isParentTAnyIdent("13"));
		}
		//Paernt*(1, _)
		TEST_METHOD(isParentTIdentAny)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentTIdentAny("6"));
			Assert::IsTrue(PKB.isParentTIdentAny("10"));
			Assert::IsTrue(PKB.isParentTIdentAny("14"));
			Assert::IsFalse(PKB.isParentTIdentAny("5"));
		}
		//Parent*(1,2)
		TEST_METHOD(isParentTIdentIdent)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentTIdentIdent("6", "7"));
			Assert::IsTrue(PKB.isParentTIdentIdent("6", "8"));
			Assert::IsTrue(PKB.isParentTIdentIdent("6", "9"));
			Assert::IsTrue(PKB.isParentTIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isParentTIdentIdent("6", "11"));
			Assert::IsTrue(PKB.isParentTIdentIdent("6", "12"));
			Assert::IsTrue(PKB.isParentTIdentIdent("10", "11"));
			Assert::IsTrue(PKB.isParentTIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isParentTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isParentTIdentIdent("14", "16"));
		}
		//Parent*(_,s2)
		TEST_METHOD(getParentTAnyEnt)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getParentTAnyEnt("assign");
			expected = { {"7"},{"9"},{"11"},{"12"},{"13"},{"15"}, {"16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTAnyEnt( "read");
			Assert::IsTrue(actual.size() == 0);
		}
		//Parent*(s1,_)
		TEST_METHOD(getParentTEntAny)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getParentTEntAny("while");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTEntAny("read");
			Assert::IsTrue(actual.size() == 0);
		}
		//Parent*(s1,s2)
		TEST_METHOD(getParentTEntEnt)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getParentTEntEnt("while", "assign");
			expected = { {"6","7"},{"6","9"},{"6","11"},{"6","12"}, {"6","13"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTEntEnt("assign", "read");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getParentTEntEnt("if", "stmt");
			expected = { {"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTEntEnt("stmt", "stmt");
			expected = { {"6","7"},{"6","8"},{"6","9"},{"6","10"},{"6","11"},{"6","12"}, {"6","13"} ,{"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

		}
		//Parent*(s,15)
		TEST_METHOD(getParentTEntIdent)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getParentTEntIdent("if", "15");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTEntIdent("assign", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getParentTEntIdent("while", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTEntIdent("stmt", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}

		//Parent*(15,s)
		TEST_METHOD(getParentTIdentEnt)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getParentTIdentEnt("14", "assign");
			expected = { {"15"}, {"16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getParentTIdentEnt("2", "assign");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getParentTIdentEnt("6", "assign");
			expected = { {"7"},{"9"},{"11"},{"12"},{"13"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getParentTIdentEnt("6", "stmt");
			expected = { {"7"}, {"8"}, {"9"}, {"10"}, {"11"}, {"12"} , {"13"} };
			Assert::IsTrue(actual == expected);
			
		}

		TEST_METHOD(isParentExist)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentExist("7"));
			Assert::IsTrue(PKB.isParentExist("8"));
			Assert::IsTrue(PKB.isParentExist("9"));
			Assert::IsTrue(PKB.isParentExist("11"));
			Assert::IsTrue(PKB.isParentExist("12"));
		}
	};
};


