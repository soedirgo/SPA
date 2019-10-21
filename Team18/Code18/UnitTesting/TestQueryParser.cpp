#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryParser.h"
#include "Query.h"
#include "Clause.h"
#include "PKB.h"
#include "PatternProcessor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	
	TEST_CLASS(TestQueryParser)
	{
	public:
		TEST_METHOD(findInitialDecleration)
		{
			vector<string> actual = QueryParser::findInitialDecleration("assign a; variable v;Select a such that Uses(a,v)");
			vector<string> expected{ "assign a", "variable v", "Select a such that Uses(a,v)" };
			Assert::AreEqual(actual == expected, true);
		}

		TEST_METHOD(splitVariablesInDeclerations)
		{
			vector<string> input = { "variable v1, v2", "while w1 ,w2", "Select v such that Follows(v,w)" };
			unordered_map<string, string> actual = QueryParser::splitVariablesInDeclerations(input);
			unordered_map<string, string> expected{ {"v1", "variable"}, {"v2", "variable"}, {"w1", "while"}, {"w2", "while"} };
			Assert::AreEqual(actual == expected, true);
		}


		TEST_METHOD(splitSelect)
		{
			vector<string> actual1 = QueryParser::splitSelect("Select v2");
			vector<string> expected1 { "v2" };
			Assert::AreEqual(actual1 == expected1, true);

			vector<string> actual2 = QueryParser::splitSelect("Select procName.procName");
			vector<string> expected2{ "procName.procName" };
			Assert::AreEqual(actual2 == expected2, true);

			vector<string> actual3 = QueryParser::splitSelect("Select procName.procName");
			vector<string> expected3{ "procName.procName" };
			Assert::AreEqual(actual3 == expected3, true);

			vector<string> actual4 = QueryParser::splitSelect("Select <procName.procName,varName.varName,value.value,stmt.stmt#>");
			vector<string> expected4{ "procName.procName","varName.varName", "value.value", "stmt.stmt#" };
			Assert::AreEqual(actual4 == expected4, true);

			vector<string> actual5 = QueryParser::splitSelect("Select <procName. procName,  varName.v arName, value.valu e, stmt.stmt#>");
			vector<string> expected5{ "procName.procName","varName.varName", "value.value", "stmt.stmt#" };
			Assert::AreEqual(actual5 == expected5, true);
		}

		TEST_METHOD(splitSuchThat)
		{
			vector<string> suchThatString = { "such that Modifies(2,\"x\")" };
			vector<pair<string, pair<string, string>>> actual = QueryParser::splitSuchThat(suchThatString);
			vector<pair<string, pair<string, string>>> expected = { {"Modifies", {"2","x"}} };
			Assert::AreEqual(actual == expected, true);

			vector<string> suchThatString2 = { "such that Modifies(2,x)" };
			vector<pair<string, pair<string, string>>> actual2 = QueryParser::splitSuchThat(suchThatString2);
			vector<pair<string, pair<string, string>>> expected2 = { {"Modifies", {"2","x"}} };
			Assert::AreEqual(actual2 == expected2, true);

			vector<string> suchThatString3 = { "such that Modifies (2   ,  x)" };
			vector<pair<string, pair<string, string>>> actual3 = QueryParser::splitSuchThat(suchThatString3);
			vector<pair<string, pair<string, string>>> expected3 = { {"Modifies", {"2","x"}} };
			Assert::AreEqual(actual3 == expected3, true);
		}

		TEST_METHOD(splitPatternCondition)
		{
			vector<string> input = { "pattern a(_, _)" };
			vector<pair<string, pair<string, string>>> actual = QueryParser::splitPattern(input);
			vector<pair<string, pair<string, string>>> expected{ {"a", {"_", "_"}} };
			Assert::AreEqual(actual == expected, true);
			
			vector<string> input2 = { "pattern a(_, a+b*c)" };
			vector<pair<string, pair<string, string>>> actual2 = QueryParser::splitPattern(input2);
			vector<pair<string, pair<string, string>>> expected2{ {"a", {"_", "_a__b__c_*+"}} };
			Assert::AreEqual(actual2 == expected2, true);

			vector<string> input3 = { "pattern a(_, _\"a+b*c\"_)" };
			vector<pair<string, pair<string, string>>> actual3 = QueryParser::splitPattern(input3);
			vector<pair<string, pair<string, string>>> expected3{ {"a", {"_", "__a__b__c_*+_"}} };
			Assert::AreEqual(actual3 == expected3, true);

			vector<string> input4 = { "pattern a(_, _  \"  a+b*c  \"  _)" };
			vector<pair<string, pair<string, string>>> actual4 = QueryParser::splitPattern(input4);
			vector<pair<string, pair<string, string>>> expected4{ {"a", {"_", "__a__b__c_*+_"}} };
			Assert::AreEqual(actual4 == expected4, true);
		}

		TEST_METHOD(initialValidation)
		{
			string expected = "Invalid";
			string actual = QueryParser::initialValidation("");
			Assert::AreEqual(actual == expected,true);
			
			string actual2 = QueryParser::initialValidation("Select v");
			string expected2 = "None";
			Assert::AreEqual(actual2 == expected2, true);

			string actual3 = QueryParser::initialValidation("variable v;");
			string expected3 = "Invalid";
			Assert::AreEqual(actual3 == expected3, true);
		}

		TEST_METHOD(declarationsValidation)
		{
			unordered_map<string, string> input{ {"1a2", "assign"},{"v", "variable"} };
			string actual = QueryParser::declarationsValidation(input);
			string expected = "Invalid";
			Assert::AreEqual(actual == expected, true);

			unordered_map<string, string> input2{ {"a1_", "assign"},{"v", "variable"} };
			string actual2 = QueryParser::declarationsValidation(input2);
			string expected2 = "Invalid";
			Assert::AreEqual(actual2 == expected2, true);
			
			unordered_map<string, string> input3{ {"a*", "assign"},{"v", "variable"} };
			string actual3 = QueryParser::declarationsValidation(input3);
			string expected3 = "Invalid";
			Assert::AreEqual(actual3 == expected3, true);

			unordered_map<string, string> input4{ {"a", "assign"},{"char", "c"} };
			string actual4 = QueryParser::declarationsValidation(input4);
			string expected4 = "Invalid";
			Assert::AreEqual(actual4 == expected4, true);
		
		}

		TEST_METHOD(selectVariablesValidation)
		{
			unordered_map<string, string> declerationVariables1 
				= {{"v","variable"}, {"a","assign"}};
			vector<string> selectVars1 {"hihiih"};
			string actual1 = QueryParser::selectVariablesValidation(declerationVariables1, selectVars1);
			string expected1 = "Invalid";
			Assert::AreEqual(actual1 == expected1, true);

			unordered_map<string, string> declerationVariables2
				= { {"v","variable"}, {"a","assign"} };
			vector<string> selectVars2{ "v","a","BOOLEAN" };
			string actual2 = QueryParser::selectVariablesValidation(declerationVariables2, selectVars2);
			string expected2 = "Invalid";
			Assert::AreEqual(actual2 == expected2, true);

			unordered_map<string, string> declerationVariables3
				= { {"c","call"}, {"p","procedure"}, {"a","assign"} };
			vector<string> selectVars3{ "p.procName","c.procName","a.procName" };
			string actual3 = QueryParser::selectVariablesValidation(declerationVariables3, selectVars3);
			string expected3 = "Invalid";
			Assert::AreEqual(actual3 == expected3, true);

			unordered_map<string, string> declerationVariables4
				= { {"c","call"}, {"p","procedure"}};
			vector<string> selectVars4{ "p.procName","c.procName"};
			string actual4 = QueryParser::selectVariablesValidation(declerationVariables4, selectVars4);
			string expected4 = "Okay";
			Assert::AreEqual(actual4 == expected4, true);

			unordered_map<string, string> declerationVariables5
				= { {"v","variable"}, {"r","read"}, {"pr","print"},{"a","assign"} };
			vector<string> selectVars5{ "v.varName","r.varName","pr.varName", "a.varName" };
			string actual5 = QueryParser::selectVariablesValidation(declerationVariables5, selectVars5);
			string expected5 = "Invalid";
			Assert::AreEqual(actual5 == expected5, true);

			unordered_map<string, string> declerationVariables6
				= { {"v","variable"}, {"r","read"}, {"pr","print"} };
			vector<string> selectVars6{ "v.varName","r.varName","pr.varName" };
			string actual6 = QueryParser::selectVariablesValidation(declerationVariables6, selectVars6);
			string expected6 = "Okay";
			Assert::AreEqual(actual6 == expected6, true);

			unordered_map<string, string> declerationVariables7
				= { {"r","constant"}, {"c","read"} };
			vector<string> selectVars7{ "r.value","c.value" };
			string actual7 = QueryParser::selectVariablesValidation(declerationVariables7, selectVars7);
			string expected7 = "Invalid";
			Assert::AreEqual(actual7 == expected7, true);

			unordered_map<string, string> declerationVariables8
				= { {"r","constant"}};
			vector<string> selectVars8{ "r.value"};
			string actual8 = QueryParser::selectVariablesValidation(declerationVariables8, selectVars8);
			string expected8 = "Okay";
			Assert::AreEqual(actual8 == expected8, true);

			unordered_map<string, string> declerationVariables9
				= { {"r","variable"} };
			vector<string> selectVars9{ "r.stmt#" };
			string actual9 = QueryParser::selectVariablesValidation(declerationVariables9, selectVars9);
			string expected9 = "Invalid";
			Assert::AreEqual(actual9 == expected9, true);

			unordered_map<string, string> declerationVariables10
				= { {"callName","call"}, {"procName","procedure"} };
			vector<string> selectVars10{ "procName.procName","procName.procName" };
			string actual10 = QueryParser::selectVariablesValidation(declerationVariables10, selectVars10);
			string expected10 = "Okay";
			Assert::AreEqual(actual10 == expected10, true);
		}

		TEST_METHOD(suchThatValidation)
		{
			unordered_map<string, string> declerationVariables1 = { {"a", "assign"}, {"v", "variable"} };
			vector<pair<string,pair<string,string>>> suchThat1 { {"Modifiess", { "a", "v" }} };
			string actual1 = QueryParser::suchThatValidation(declerationVariables1, suchThat1);
			string expected1 = "Invalid";
			Assert::AreEqual(actual1 == expected1, true);

			unordered_map<string, string> declerationVariables2 = { {"a", "assign"}, {"v", "variable"} };
			vector<pair<string, pair<string, string>>> suchThat2{ {"", { "a", "v" }} };
			string actual2 = QueryParser::suchThatValidation(declerationVariables2, suchThat2);
			string expected2 = "Invalid";
			Assert::AreEqual(actual2 == expected2, true);

			unordered_map<string, string> declerationVariables3 = { {"a", "assign"}, {"v", "variable"} };
			vector<pair<string, pair<string, string>>> suchThat3{ {"Parent*", { "a-", "2" }} };
			string actual3 = QueryParser::suchThatValidation(declerationVariables3, suchThat3);
			string expected3 = "Semantic Invalid";
			Assert::AreEqual(actual3 == expected3, true);

			unordered_map<string, string> declerationVariables4 = { {"a", "assign"}, {"v", "variable"} };
			vector<pair<string, pair<string, string>>> suchThat4{ {"Next*", { "2", "v" }} };
			string actual4 = QueryParser::suchThatValidation(declerationVariables4, suchThat4);
			string expected4 = "Semantic Invalid";
			Assert::AreEqual(actual4 == expected4, true);

			unordered_map<string, string> declerationVariables5 = { {"a", "assign"}, {"v", "variable"} };
			vector<pair<string, pair<string, string>>> suchThat5{ {"Uses", { "a*", "v" }} };
			string actual5 = QueryParser::suchThatValidation(declerationVariables5, suchThat5);
			string expected5 = "Semantic Invalid";
			Assert::AreEqual(actual5 == expected5, true);

			unordered_map<string, string> declerationVariables6 = { {"a", "assign"}, {"v", "variable"} };
			vector<pair<string, pair<string, string>>> suchThat6{ {"Modifies", { "v", "v" }} };
			string actual6 = QueryParser::suchThatValidation(declerationVariables6, suchThat6);
			string expected6 = "Semantic Invalid";
			Assert::AreEqual(actual6 == expected6, true);

			unordered_map<string, string> declerationVariables7 = { {"a", "procedure"}, {"v", "variable"} };
			vector<pair<string, pair<string, string>>> suchThat7{ {"Calls", { "a", "v" }} };
			string actual7 = QueryParser::suchThatValidation(declerationVariables7, suchThat7);
			string expected7 = "Semantic Invalid";
			Assert::AreEqual(actual7 == expected7, true);
		}

		TEST_METHOD(infixToRPNexpression)
		{
			string input = "a+b";
			string actual = PatternProcessor::infixtoRPNexpression(input);
			string expected = " a  b +";
			Assert::AreEqual(actual == expected, true);

			string input2 = "a+b*c";
			string actual2 = PatternProcessor::infixtoRPNexpression(input2);
			string expected2 = " a  b  c *+";
			Assert::AreEqual(actual2 == expected2, true);

			string input3 = "A+B*C";
			string actual3 = PatternProcessor::infixtoRPNexpression(input3);
			string expected3 = " A  B  C *+";
			Assert::AreEqual(actual3 == expected3, true);

			string input4 = "(A+B)*C";
			string actual4 = PatternProcessor::infixtoRPNexpression(input4);
			string expected4 = " A  B + C *";
			Assert::AreEqual(actual4 == expected4, true);

			string input5 = "(A+B)*(C+D)";
			string actual5 = PatternProcessor::infixtoRPNexpression(input5);
			string expected5 = " A  B + C  D +*";
			Assert::AreEqual(actual5 == expected5, true);

		}
		
	};
	
}
