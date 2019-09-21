#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "DesignExtractor.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(DesignExtractorTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**
			   SIMPLE program:
			   _   procedure main {
			   1.      x = 1
			   2.      if (x == y) then {
			   3.          z = 0;
			   4.		   if ( x == y ) then {
			   5.			  if ( x ==  y) then {
			   6.				z = 0;
							  else {
			   7.				z = 1; }
						   } else {
			   8.			   z = 1;
			   _       } else {
			   9.          z = 1;
			   _       }
				 }
			*/
			
			PKB pkb;
			pkb.clear();

			
			
			pkb.insertParentRelation(2, 3);
			pkb.insertParentRelation(2, 4);
			pkb.insertParentRelation(2, 9);
			pkb.insertParentRelation(4, 5);
			pkb.insertParentRelation(4, 8);
			pkb.insertParentRelation(5, 6);
			pkb.insertParentRelation(5, 7);

			
			pkb.insertFollowRelation(1, 2);
			pkb.insertFollowRelation(2, 9);
			pkb.insertFollowRelation(3, 4);
			pkb.insertFollowRelation(4, 8);
			pkb.insertFollowRelation(5, 7);

			DesignExtractor designExtractor;
			designExtractor.extractDesign();
			
		}
		
		TEST_METHOD(FollowStarRelationship)
		{
			Assert::IsTrue(PKB().isFollowStarRelationship(1, 2));
			Assert::IsTrue(PKB().isFollowStarRelationship(2, 9));
			Assert::IsTrue(PKB().isFollowStarRelationship(3, 4));
			Assert::IsTrue(PKB().isFollowStarRelationship(4, 8));
			Assert::IsTrue(PKB().isFollowStarRelationship(5, 7));

		}
		TEST_METHOD(ParentStarRelationship)
		{
			Assert::IsTrue(PKB().isParentStarRelationship(2, 3));
			Assert::IsTrue(PKB().isParentStarRelationship(2, 4));
			Assert::IsTrue(PKB().isParentStarRelationship(2, 9));
			Assert::IsTrue(PKB().isParentStarRelationship(4, 5));
			Assert::IsTrue(PKB().isParentStarRelationship(4, 8));
			Assert::IsTrue(PKB().isParentStarRelationship(5, 6));
			Assert::IsTrue(PKB().isParentStarRelationship(5, 7));

			Assert::IsTrue(PKB().isParentStarRelationship(2, 5));
			Assert::IsTrue(PKB().isParentStarRelationship(2, 8));
			Assert::IsTrue(PKB().isParentStarRelationship(2, 6));
			Assert::IsTrue(PKB().isParentStarRelationship(2, 7));
			Assert::IsTrue(PKB().isParentStarRelationship(4, 6));
			Assert::IsTrue(PKB().isParentStarRelationship(4, 7));
		}
		
	};
};


