/**
 * \file 	ClassTests.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	18 September 2014
 * \brief 	Unit tests for all classes. Included in single file for regression testing purposes.
 */

#include <gtest/gtest.h>

//Needed to compile the tests in my project:
#include "Manager.h"
#include "CollisionManager.h"
#include "Tank.h"
#include "Missile.h"
#include "Orientation.h"
#include "Structures.h"



///*================Tests for CollisionManager Class============*/

///addNewEntity
//TEST(CollisionManager, ifInvalidPointerTypeGivenThrowsException)
//{
//
//}
//
//TEST(CollisionManager, ifInvalidPointerObjectGivenThrowsException)
//{
//
//}

///isCollision
//TEST(CollisionManager, ifInvalidRectangleGivenThrowsException)
//{
//
//}

TEST(CollisionTest, indicatesCollisionHasTakenPlace)
{
    rect_corners rect_A;
    rect_corners rect_B;

    rect_A.upper_left.x = 1.0;
    rect_A.upper_left.y = 8.0;
    rect_A.upper_right.x = 5.0;
    rect_A.upper_right.y = 8.0;
    rect_A.lower_left.x = 1.0;
    rect_A.lower_left.y = 1.0;
    rect_A.lower_right.x = 5.0;
    rect_A.lower_right.y = 1.0;

    rect_B.upper_left.x = 2.0;
    rect_B.upper_left.y = 9.0;
    rect_B.upper_right.x = 6.0;
    rect_B.upper_right.y = 8.0;
    rect_B.lower_left.x = 2.0;
    rect_B.lower_left.y = 2.0;
    rect_B.lower_right.x = 6.0;
    rect_B.lower_right.y = 2.0;

   // EXPECT_TRUE(isCollision(rect_A, rect_B));
}

//TEST(CollisionManager, indicatesNoCollisionHasTakenPlace)
//{
//
//
//}

///isOverlap
//TEST(CollisionManager, ifInvalidAxisGivenThrowsException)
//{
//
//}
//
//TEST(CollisionManager, ifInvalidRectangleGivenThrowsException)
//{
//
//}

//TEST(CollisionManager, returnsCorrectOverlapOutcome)
//{
//
//}

///calculateAllProjections
//TEST(CollisionManager, ifInvalidVectorArgumentGivenThrowsException)
//{
//
//}
//
//TEST(CollisionManager, ifInvalidRectangleGivenThrowsException)
//{
//
//}

//TEST(CollisionManager,  modifiesAxisProjectionsVectorCorrectly)
//{
//
//}

///calculateMaxAndMinProjections
//TEST(CollisionManager, ifInvalidVectorArgumentGivenThrowsException)
//{
//
//}
//
//TEST(CollisionManager, ifInvalidRectangleGivenThrowsException)
//{
//
//}

//TEST(CollisionManager, modifiesMaxVectorProjectionCorrectly)
//{
//
//}

//TEST(CollisionManager, modifiesMinVectorProjectionsCorrectly)
//{
//
//}

///setCollisionStates
//TEST(CollisionManager, ifInvalidPointerGivenThrowsException)
//{
//
//}
//
//TEST(CollisionManger, ifInvalidPointerObjectGivenThrowsException)
//{
//
//}

//TEST(CollisionManager, collisionStatesSetCorrectly)
//{
//
//}


//*==============Tests for Orientation Class=======*/
TEST(Orientation, constructorCorrectlyAssignsInitialParameters)
{
    float originX = 10.0;
    float originY = 12.0;
    float rotation = 20.0;
    float height = 5;
    float width = 10;

    Orientation orientationTest(originX,originY,width,height,rotation);

    EXPECT_EQ(orientationTest.getOriginX(), originX);
    EXPECT_EQ(orientationTest.getOriginY(), originY);
    EXPECT_EQ(orientationTest.getRotation(), rotation);
    EXPECT_EQ(orientationTest.getHeight(), height);
    EXPECT_EQ(orientationTest.getWidth(), width);
}

TEST(Orientation, equalityOpperatorCorresctlyReturnsValues)
{
    Orientation orientationTest1(10,10,10,10,10);
    Orientation orientationTest2(10,10,10,10,10);
    Orientation orientationTest3(0,10,10,10,10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);
    EXPECT_FALSE(orientationTest1 == orientationTest3);
}

TEST(Orientation, moveFunctionCorrectlyChangesCoodinates)
{

    Orientation orientationTest1(10,10,10,10,10);
    Orientation orientationTest2(20,20,10,10,10);

    orientationTest1.move(10,10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);

    orientationTest1.move(-10,-10);
    orientationTest2.move(-10,-10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);
}

TEST(Orientation, rotateFunctionCorrectlyChangesCoordinates)
{
    Orientation orientationTest1(10,10,10,10,10);
    Orientation orientationTest2(10,10,10,10,20);

    orientationTest1.rotate(10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);

    orientationTest2.rotate(360);

    EXPECT_TRUE(orientationTest1 == orientationTest2);
}

TEST(Orientation, getGlobalBoundsCorrectlyReturnsBoundingBox)
{
    Orientation orientationTest1(10,10,10,10,10);
    Orientation orientationTest2(10,10,10,10,10);

    auto boundBox1 = orientationTest1.getGlobalBounds();
    auto boundBox2 = orientationTest2.getGlobalBounds();

    EXPECT_EQ(boundBox1.upper_left.x, boundBox2.upper_left.x);
    EXPECT_EQ(boundBox1.upper_left.y, boundBox2.upper_left.y);

    orientationTest1.move(10,10);

    boundBox1 = orientationTest1.getGlobalBounds();

    EXPECT_NE(boundBox1.upper_left.x, boundBox2.upper_left.x);
    EXPECT_NE(boundBox1.upper_left.y, boundBox2.upper_left.y);

    orientationTest2.move(10,10);

    boundBox2 = orientationTest2.getGlobalBounds();

    EXPECT_EQ(boundBox1.lower_left.x, boundBox2.lower_left.x);
    EXPECT_EQ(boundBox1.lower_left.y, boundBox2.lower_left.y);
}

//TEST(Orientation, throwsExceptionForInvalidConstructorParameters)
//{
//
//}

//*================================================*/



//*================Tests for Tank Class============*/
//TEST(Tank, ifInvalidCoOrdinatesThrowsException)
//{
//
//}
//
//TEST(Tank, returnsCorrectEntityType)
//{
//
//}
//
//TEST(Tank, movesForwardCorrectly)
//{
//
//}
//
//TEST(Tank, movesBackwardCorrectly)
//{
//
//}
//
//TEST(Tank, rotatesLeftCorrectly)
//{
//
//}
//
//TEST(Tank, rotatesRightCorrectly)
//{
//
//}
//
//TEST(Tank, CollidableStateCorrectlyReadAndSet)
//{
//
//}
//
//TEST(Tank, BlockableStateCorrectlyReadAndSet)
//{
//
//}
//
//*================Tests for Missile Class============*/
//TEST(Missile, ifInvalidCoOrdinatesThrowsException)
//{
//
//}
//
//TEST(Missile, returnsCorrectEntityType)
//{
//
//}
//
//TEST(Missile, movesForwardCorrectly)
//{
//
//}
//
//TEST(Missile, movesBackwardCorrectly)
//{
//
//}
//
//TEST(Missile, rotatesLeftCorrectly)
//{
//
//}
//
//TEST(Missile, rotatesRightCorrectly)
//{
//
//}
//
//TEST(Missile, CollidableStateCorrectlyReadAndSet)
//{
//
//}
//
//TEST(Missile, BlockableStateCorrectlyReadAndSet)
//{
//
//}
