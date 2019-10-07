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

			
			
			pkb.setParentRelation(2, 3);
			pkb.setParentRelation(2, 4);
			pkb.setParentRelation(2, 9);
			pkb.setParentRelation(4, 5);
			pkb.setParentRelation(4, 8);
			pkb.setParentRelation(5, 6);
			pkb.setParentRelation(5, 7);

			
			pkb.setFollowsRelation(1, 2);
			pkb.setFollowsRelation(2, 9);
			pkb.setFollowsRelation(3, 4);
			pkb.setFollowsRelation(4, 8);
			pkb.setFollowsRelation(5, 7);

			DesignExtractor designExtractor;
			designExtractor.extractDesign();
			
		}
		
		TEST_METHOD(FollowStarRelationship)
		{
			Assert::IsTrue(PKB().isFollowsStarRelationship(1, 2));
			Assert::IsTrue(PKB().isFollowsStarRelationship(2, 9));
			Assert::IsTrue(PKB().isFollowsStarRelationship(3, 4));
			Assert::IsTrue(PKB().isFollowsStarRelationship(4, 8));
			Assert::IsTrue(PKB().isFollowsStarRelationship(5, 7));
			Assert::IsTrue(PKB().isFollowsStarRelationship(1, 9));
			Assert::IsTrue(PKB().isFollowsStarRelationship(3, 8));

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


