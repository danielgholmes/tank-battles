/**
 * \file 	ClassTests.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	18 September 2014
 * \brief 	Unit tests for all classes. Included in single file for regression testing purposes.
 */

#include <gtest/gtest.h>

//Needed to compile the tests in my project:
#include "Structures.h"
#include "Orientation.h"

//#include "Manager.h"
//#include "CollisionManager.h"

#include "Tank.h"
#include "Missile.h"
#include "Barrier.h"


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

//TEST(CollisionTest, indicatesCollisionHasTakenPlace)
//{
//    rect_corners rect_A;
//    rect_corners rect_B;
//
//    rect_A.upper_left.x = 1.0;
//    rect_A.upper_left.y = 8.0;
//    rect_A.upper_right.x = 5.0;
//    rect_A.upper_right.y = 8.0;
//    rect_A.lower_left.x = 1.0;
//    rect_A.lower_left.y = 1.0;
//    rect_A.lower_right.x = 5.0;
//    rect_A.lower_right.y = 1.0;
//
//    rect_B.upper_left.x = 2.0;
//    rect_B.upper_left.y = 9.0;
//    rect_B.upper_right.x = 6.0;
//    rect_B.upper_right.y = 8.0;
//    rect_B.lower_left.x = 2.0;
//    rect_B.lower_left.y = 2.0;
//    rect_B.lower_right.x = 6.0;
//    rect_B.lower_right.y = 2.0;
//
//    EXPECT_TRUE(isCollision(rect_A, rect_B));
//}

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


///*==============Tests for Orientation Class=======*/
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

///*================================================*/



///*================Tests for Tank Class============*/

TEST(Tank, ifInvalidCoOrdinatesThrowsException)
{
    EXPECT_THROW({Tank TestTank1(-10,10,10,p1_tank);},InvalidConstructorArguments);
    EXPECT_THROW({Tank TestTank1(10,-10,10,p1_tank);},InvalidConstructorArguments);
    EXPECT_THROW({Tank TestTank1(10,10,-10,p1_tank);},InvalidConstructorArguments);
    EXPECT_NO_THROW({Tank TestTank1(10,10,10,p1_tank);});
    EXPECT_THROW({Tank TestTank1(10,10,10,p1_mine);},InvalidConstructorArguments);
}


TEST(Tank, returnsCorrectEntityType)
{
    Tank TestTank1(10,10,10,p1_tank);
    Tank TestTank2(10,10,10,p2_tank);

    EXPECT_EQ(TestTank1.getType(),p1_tank);
    EXPECT_EQ(TestTank2.getType(),p2_tank);
}

TEST(Tank, returnsCorrectCoordinatesFromGetPosition)
{
    Tank TestTank1(10,10,10,p1_tank);
    Tank TestTank2(20,20,10,p2_tank);

    EXPECT_EQ(TestTank1.getPositionX(),10);
    EXPECT_EQ(TestTank1.getPositionY(),10);

    EXPECT_EQ(TestTank2.getPositionX(),20);
    EXPECT_EQ(TestTank2.getPositionY(),20);
}

TEST(Tank, returnsCorrectCoordinatesFromGetDrawPosition)
{
    Tank TestTank1(10,10,10,p1_tank);
    Tank TestTank2(20,20,10,p2_tank);

    EXPECT_EQ(TestTank1.getDrawPositionX(),10);
    EXPECT_EQ(TestTank1.getDrawPositionY(),10);

    EXPECT_EQ(TestTank2.getDrawPositionX(),20);
    EXPECT_EQ(TestTank2.getDrawPositionY(),20);
}

TEST(Tank, returnsCorrectOrientationValue)
{
    Tank TestTank1(10,10,10,p1_tank);
    EXPECT_EQ(TestTank1.getOrientation(),10);
}

TEST(Tank, returnsCorrectDrawRotationValue)
{
    Tank TestTank1(10,10,10,p1_tank);
    EXPECT_EQ(TestTank1.getDrawRotation(),10);
}

TEST(Tank, movesForwardCorrectly)
{
    Tank TestTank1(10,10,0,p1_tank);
    TestTank1.moveForward();
    EXPECT_EQ(TestTank1.getPositionX(),15);
    EXPECT_EQ(TestTank1.getPositionY(),10);

    Tank TestTank2(10,10,90,p1_tank);
    TestTank2.moveForward();
    EXPECT_EQ(TestTank2.getPositionX(),10);
    EXPECT_EQ(TestTank2.getPositionY(),15);

    Tank TestTank3(10,10,180,p1_tank);
    TestTank3.moveForward();
    EXPECT_EQ(TestTank3.getPositionX(),5);
    EXPECT_EQ(TestTank3.getPositionY(),10);

    Tank TestTank4(10,10,270,p1_tank);
    TestTank4.moveForward();
    EXPECT_EQ(TestTank4.getPositionX(),10);
    EXPECT_EQ(TestTank4.getPositionY(),5);
}

TEST(Tank, movesBackwardCorrectly)
{
    Tank TestTank1(10,10,0,p1_tank);
    TestTank1.moveBackward();
    EXPECT_EQ(TestTank1.getPositionX(),5);
    EXPECT_EQ(TestTank1.getPositionY(),10);

    Tank TestTank2(10,10,90,p1_tank);
    TestTank2.moveBackward();
    EXPECT_EQ(TestTank2.getPositionX(),10);
    EXPECT_EQ(TestTank2.getPositionY(),5);

    Tank TestTank3(10,10,180,p1_tank);
    TestTank3.moveBackward();
    EXPECT_EQ(TestTank3.getPositionX(),15);
    EXPECT_EQ(TestTank3.getPositionY(),10);

    Tank TestTank4(10,10,270,p1_tank);
    TestTank4.moveBackward();
    EXPECT_EQ(TestTank4.getPositionX(),10);
    EXPECT_EQ(TestTank4.getPositionY(),15);
}

TEST(Tank, rotatesLeftAndRightCorrectly)
{
    Tank TestTank1(10,10,0,p1_tank);
    TestTank1.rotateLeft();
    EXPECT_EQ(TestTank1.getOrientation(), 2);

    TestTank1.rotateRight();
    TestTank1.rotateRight();
    EXPECT_EQ(TestTank1.getOrientation(), 358);

    Tank TestTank2(10,10,358,p1_tank);
    TestTank2.rotateLeft();
    TestTank2.rotateLeft();
    EXPECT_EQ(TestTank2.getOrientation(), 2);
}

TEST(Tank, booleanVariablesAreCorrectlySetAndRetrieved)
{
    Tank TestTank1(10,10,0,p1_tank);

    TestTank1.setBlocked();
    TestTank1.setCollided();

    EXPECT_TRUE(TestTank1.isBlocked());
    EXPECT_TRUE(TestTank1.isDeleted());

    TestTank1.setUnblocked();

    EXPECT_FALSE(TestTank1.isBlocked());

}
///*===================================================*/

///*================Tests for Missile Class============*/

TEST(Missile, ifInvalidCoOrdinatesThrowsException)
{
    EXPECT_THROW({Missile TestMissile(-10,10,10,p1_missile);},InvalidConstructorArgumentsMissile);
    EXPECT_THROW({Missile TestMissile(10,-10,10,p1_missile);},InvalidConstructorArgumentsMissile);
    EXPECT_THROW({Missile TestMissile(10,10,-10,p1_missile);},InvalidConstructorArgumentsMissile);
    EXPECT_NO_THROW({Missile TestMissile(10,10,10,p1_missile);});
    EXPECT_THROW({Missile TestMissile(10,10,10,p1_mine);},InvalidConstructorArgumentsMissile);
}


TEST(Missile, returnsCorrectEntityType)
{
    Missile TestMissile1(10,10,10,p1_missile);
    Missile TestMissile2(10,10,10,p2_missile);

    EXPECT_EQ(TestMissile1.getType(),p1_missile);
    EXPECT_EQ(TestMissile2.getType(),p2_missile);
}

TEST(Missile, returnsCorrectCoordinatesFromGetDrawPosition)
{
    Missile TestMissile1(10,10,10,p1_missile);
    Missile TestMissile2(20,20,10,p2_missile);

    EXPECT_EQ(TestMissile1.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile1.getDrawPositionY(),10);

    EXPECT_EQ(TestMissile2.getDrawPositionX(),20);
    EXPECT_EQ(TestMissile2.getDrawPositionY(),20);
}

TEST(Missile, returnsCorrectDrawRotationValue)
{
    Missile TestMissile1(10,10,10,p1_missile);
    EXPECT_EQ(TestMissile1.getDrawRotation(),10);
}

TEST(Missile, movesForwardCorrectly)
{
    Missile TestMissile1(10,10,0,p1_missile);
    TestMissile1.moveForward();
    EXPECT_EQ(TestMissile1.getDrawPositionX(),30);
    EXPECT_EQ(TestMissile1.getDrawPositionY(),10);

    Missile TestMissile2(10,10,90,p1_missile);
    TestMissile2.moveForward();
    EXPECT_EQ(TestMissile2.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile2.getDrawPositionY(),30);

    Missile TestMissile3(10,10,180,p1_missile);
    TestMissile3.moveForward();
    EXPECT_EQ(TestMissile3.getDrawPositionX(),-10);
    EXPECT_EQ(TestMissile3.getDrawPositionY(),10);

    Missile TestMissile4(10,10,270,p1_missile);
    TestMissile4.moveForward();
    EXPECT_EQ(TestMissile4.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile4.getDrawPositionY(),-10);
}

TEST(Missile, movesBackwardsCorrectly)
{
    Missile TestMissile1(10,10,0,p1_missile);
    TestMissile1.moveBackward();
    EXPECT_EQ(TestMissile1.getDrawPositionX(),-10);
    EXPECT_EQ(TestMissile1.getDrawPositionY(),10);

    Missile TestMissile2(10,10,90,p1_missile);
    TestMissile2.moveBackward();
    EXPECT_EQ(TestMissile2.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile2.getDrawPositionY(),-10);

    Missile TestMissile3(10,10,180,p1_missile);
    TestMissile3.moveBackward();
    EXPECT_EQ(TestMissile3.getDrawPositionX(),30);
    EXPECT_EQ(TestMissile3.getDrawPositionY(),10);

    Missile TestMissile4(10,10,270,p1_missile);
    TestMissile4.moveBackward();
    EXPECT_EQ(TestMissile4.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile4.getDrawPositionY(),30);
}

TEST(Missile, rotatesLeftAndRightCorrectly)
{
    Missile TestMissile1(10,10,0,p1_missile);
    TestMissile1.rotateLeft();
    EXPECT_EQ(TestMissile1.getDrawRotation(), 45);

    TestMissile1.rotateRight();
    TestMissile1.rotateRight();
    EXPECT_EQ(TestMissile1.getDrawRotation(), 315);

    Missile TestMissile2(10,10,315,p1_missile);
    TestMissile2.rotateLeft();
    TestMissile2.rotateLeft();
    EXPECT_EQ(TestMissile2.getDrawRotation(), 45);
}

TEST(Missile, booleanVariablesAreCorrectlySetAndRetrieved)
{
    Missile TestMissile1(10,10,0,p1_missile);

    TestMissile1.setBlocked();
    TestMissile1.setCollided();

    EXPECT_TRUE(TestMissile1.isBlocked());
    EXPECT_TRUE(TestMissile1.isDeleted());

    TestMissile1.setUnblocked();

    EXPECT_FALSE(TestMissile1.isBlocked());
}

///*===================================================*/

///*================Tests for Barrier Class============*/

TEST(Barrier, ifInvalidCoOrdinatesThrowsException)
{
    EXPECT_THROW({Barrier TestBarrier(-10,10,barrier);},InvalidConstructorArgumentsMissile);
    EXPECT_THROW({Barrier TestBarrier(10,-10,barrier);},InvalidConstructorArgumentsMissile);
    EXPECT_NO_THROW({Barrier TestBarrier(10,10,barrier);});
    EXPECT_THROW({Barrier TestBarrier(10,10,p1_mine);},InvalidConstructorArgumentsMissile);
}

TEST(Barrier, returnsCorrectEntityType)
{
    Barrier TestBarrier(10,10,barrier);

    EXPECT_EQ(TestBarrier.getType(),barrier);
}

TEST(Barrier, returnCorrectRectangleVertices)
{
    //barriers are 5x5
    Barrier TestBarrier(10,10,barrier);
    rect_corners rect;

    rect.upper_left.x = 7.5;
    rect.upper_left.y = 12.5;
    rect.upper_right.x = 12.5;
    rect.upper_right.y = 12.5;
    rect.lower_left.x = 7.5;
    rect.lower_left.y = 7.5;
    rect.lower_right.x = 12.5;
    rect.lower_right.y = 7.5;

    EXPECT_EQ(TestBarrier.getBoundingBox().upper_left.x,rect.upper_left.x);
    EXPECT_EQ(TestBarrier.getBoundingBox().upper_left.y,rect.upper_left.y);
    EXPECT_EQ(TestBarrier.getBoundingBox().upper_right.x,rect.upper_right.x);
    EXPECT_EQ(TestBarrier.getBoundingBox().upper_right.y,rect.upper_right.y);
}

TEST(Barrier, returnsCorrectCoordinatesFromGetDrawPosition)
{
    Barrier TestBarrier1(10,10,barrier);
    Barrier TestBarrier2(20,20,barrier);

    EXPECT_EQ(TestBarrier1.getDrawPositionX(),10);
    EXPECT_EQ(TestBarrier1.getDrawPositionY(),10);

    EXPECT_EQ(TestBarrier2.getDrawPositionX(),20);
    EXPECT_EQ(TestBarrier2.getDrawPositionY(),20);
}

TEST(Barrier, returnsCorrectDrawRotationValue)
{
    Barrier TestBarrier(10,10,barrier);
    EXPECT_EQ(TestBarrier.getDrawRotation(),0);
}


///*===================================================*/

///*================Tests for Mine Class============*/



///*===================================================*/

