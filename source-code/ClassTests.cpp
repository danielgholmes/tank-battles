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
#include "GameManagementData.h"
#include "GameStateData.h"

#include "Manager.h"
#include "GameStateManager.h"
#include "CollisionManager.h"
#include "TrackingManager.h"
#include "MoveManager.h"
#include "DestructionManager.h"
#include "TurretManager.h"


#include "Tank.h"
#include "Missile.h"
#include "Barrier.h"
#include "Mine.h"
#include "GeometryEngine.h"
#include "Turret.h"

#define MISSILE_SPEED 8
#define TANK_SPEED 3
#define MISSILE_ROT_SPEED 45
#define TANK_ROT_SPEED 5
#define TURRET_ROTATION_SPEED -2
#define PI          3.141592653589793238462643383279502884L




///*==============Tests for Orientation Class=======*/
TEST(Orientation, constructorCorrectlyAssignsInitialParameters)
{
    float originX = 10.0;
    float originY = 12.0;
    float rotation = 20.0;
    float height = 5;
    float width = 10;

    Orientation orientationTest(originX,originY,width,height,rotation, true);

    EXPECT_EQ(orientationTest.getOriginX(), originX);
    EXPECT_EQ(orientationTest.getOriginY(), originY);
    EXPECT_EQ(orientationTest.getRotation(), rotation);
    EXPECT_EQ(orientationTest.getHeight(), height);
    EXPECT_EQ(orientationTest.getWidth(), width);
}

TEST(Orientation, equalityOpperatorCorresctlyReturnsValues)
{
    Orientation orientationTest1(10,10,10,10,10, true);
    Orientation orientationTest2(10,10,10,10,10, true);
    Orientation orientationTest3(0,10,10,10,10, true);

    EXPECT_TRUE(orientationTest1 == orientationTest2);
    EXPECT_FALSE(orientationTest1 == orientationTest3);
}

TEST(Orientation, moveFunctionCorrectlyChangesCoodinates)
{

    Orientation orientationTest1(10,10,10,10,10, true);
    Orientation orientationTest2(20,20,10,10,10, true);

    orientationTest1.move(10,10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);

    orientationTest1.move(-10,-10);
    orientationTest2.move(-10,-10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);
}

TEST(Orientation, rotateFunctionCorrectlyChangesCoordinates)
{
    Orientation orientationTest1(10,10,10,10,10,true);
    Orientation orientationTest2(10,10,10,10,20,true);

    orientationTest1.rotate(10);

    EXPECT_TRUE(orientationTest1 == orientationTest2);

    orientationTest2.rotate(360);

    EXPECT_TRUE(orientationTest1 == orientationTest2);
}

TEST(Orientation, getGlobalBoundsCorrectlyReturnsBoundingBox)
{
    Orientation orientationTest1(10,10,10,10,10,true);
    Orientation orientationTest2(10,10,10,10,10,true);

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

TEST(Orientation, throwsExceptionForInvalidStateOfCoordinateData)
{
    Orientation testOrientation(-101,-101,-360,10,10, true);

    EXPECT_THROW(testOrientation.getOriginX(),InvalidStateOfCoordinates);
    EXPECT_NO_THROW({Orientation TestOrientation(10,10,10,10,10, true);});

}

///*================================================*/



///*================Tests for Tank Class============*/

TEST(Tank, ifInvalidCoOrdinatesThrowsException)
{
    EXPECT_ANY_THROW({Tank TestTank1(-10,10,10,p1_tank);});
    EXPECT_ANY_THROW({Tank TestTank1(10,-10,10,p1_tank);});
    EXPECT_ANY_THROW({Tank TestTank1(10,10,-10,p1_tank);});
    EXPECT_NO_THROW({Tank TestTank1(10,10,10,p1_tank);});
    EXPECT_THROW({Tank TestTank1(10,10,10,p1_missile);}, InvalidConstructorArgumentsTank);
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
    float rotation = 0;
    Tank TestTank1(10,10,rotation,p1_tank);
    TestTank1.moveForward();
    EXPECT_EQ(TestTank1.getPositionX(),10 + TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank1.getPositionY(),10 + TANK_MOVE_SPEED*sin((rotation*PI)/180.0));

    rotation = 90;
    Tank TestTank2(10,10,rotation,p1_tank);
    TestTank2.moveForward();
    EXPECT_EQ(TestTank2.getPositionX(),10 + TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank2.getPositionY(),10 + TANK_SPEED*sin((rotation*PI)/180.0));

    rotation = 180;
    Tank TestTank3(10,10,rotation,p1_tank);
    TestTank3.moveForward();
    EXPECT_EQ(TestTank3.getPositionX(),10 + TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank3.getPositionY(),10 + TANK_SPEED*sin((rotation*PI)/180.0));

    rotation = 270;
    Tank TestTank4(10,10,rotation,p1_tank);
    TestTank4.moveForward();
    EXPECT_EQ(TestTank4.getPositionX(),10 + TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank4.getPositionY(),10 + TANK_SPEED*sin((rotation*PI)/180.0));
}

TEST(Tank, movesBackwardCorrectly)
{
    float rotation = 0;
    Tank TestTank1(10,10,rotation,p1_tank);
    TestTank1.moveBackward();
    EXPECT_EQ(TestTank1.getPositionX(),10 - TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank1.getPositionY(),10 - TANK_SPEED*sin((rotation*PI)/180.0));

    rotation = 90;
    Tank TestTank2(10,10,rotation,p1_tank);
    TestTank2.moveBackward();
    EXPECT_EQ(TestTank2.getPositionX(),10 - TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank2.getPositionY(),10 - TANK_SPEED*sin((rotation*PI)/180.0));

    rotation = 180;
    Tank TestTank3(10,10,rotation,p1_tank);
    TestTank3.moveBackward();
    EXPECT_EQ(TestTank3.getPositionX(),10 - TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank3.getPositionY(),10 - TANK_SPEED*sin((rotation*PI)/180.0));

    rotation = 270;
    Tank TestTank4(10,10,rotation,p1_tank);
    TestTank4.moveBackward();
    EXPECT_EQ(TestTank4.getPositionX(),10 - TANK_SPEED*cos((rotation*PI)/180.0));
    EXPECT_EQ(TestTank4.getPositionY(),10 - TANK_SPEED*sin((rotation*PI)/180.0));
}

TEST(Tank, rotatesLeftAndRightCorrectly)
{
    Tank TestTank1(10,10,0,p1_tank);
    TestTank1.rotateLeft();
    EXPECT_EQ(TestTank1.getOrientation(), 0 + TANK_ROT_SPEED);

    TestTank1.rotateRight();
    TestTank1.rotateRight();
    EXPECT_EQ(TestTank1.getOrientation(), 360 - TANK_ROT_SPEED);

    Tank TestTank2(10,10,358,p1_tank);
    TestTank2.rotateLeft();
    TestTank2.rotateLeft();
    EXPECT_EQ(TestTank2.getOrientation(), 8);
}

TEST(Tank, booleanVariablesAreCorrectlySetAndRetrieved)
{
    Tank TestTank1(10,10,0,p1_tank);

    TestTank1.setBlocked(blocked);
    TestTank1.setCollided();

    EXPECT_EQ(TestTank1.isBlocked(),blocked);
    EXPECT_TRUE(TestTank1.isDeleted());

    TestTank1.setUnblocked();

    EXPECT_EQ(TestTank1.isBlocked(), unblocked);

}
///*===================================================*/

///*================Tests for Missile Class============*/

TEST(Missile, ifInvalidCoOrdinatesThrowsException)
{
    EXPECT_ANY_THROW({Missile TestTank1(-10,10,10,p1_missile);});
    EXPECT_ANY_THROW({Missile TestTank1(10,-10,10,p1_missile);});
    EXPECT_ANY_THROW({Missile TestTank1(10,10,-10,p1_missile);});
    EXPECT_NO_THROW({Missile TestTank1(10,10,10,p1_missile);});
    EXPECT_THROW({Missile TestTank1(10,10,10,p1_tank);}, InvalidConstructorArgumentsMissile);
}


TEST(Missile, returnsCorrectEntityType)
{
    Missile TestMissile1(10,10,10,p1_missile);
    Missile TestMissile2(10,10,10,p2_missile);
    Missile TestMissile3(10,10,10,turret_missile);

    EXPECT_EQ(TestMissile1.getType(),p1_missile);
    EXPECT_EQ(TestMissile2.getType(),p2_missile);
    EXPECT_EQ(TestMissile3.getType(),turret_missile);
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
    float rotation = 0;
    Missile TestMissile1(10,10,rotation,p1_missile);
    TestMissile1.moveForward();
    EXPECT_EQ(TestMissile1.getDrawPositionX(),10 + MISSILE_SPEED);
    EXPECT_EQ(TestMissile1.getDrawPositionY(),10);

    rotation = 90;
    Missile TestMissile2(10,10,rotation,p1_missile);
    TestMissile2.moveForward();
    EXPECT_EQ(TestMissile2.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile2.getDrawPositionY(),10 + MISSILE_SPEED);

    rotation = 180;
    Missile TestMissile3(10,10,rotation,p1_missile);
    TestMissile3.moveForward();
    EXPECT_EQ(TestMissile3.getDrawPositionX(),10 - MISSILE_SPEED);
    EXPECT_EQ(TestMissile3.getDrawPositionY(),10);

    rotation = 270;
    Missile TestMissile4(10,10,rotation,p1_missile);
    TestMissile4.moveForward();
    EXPECT_EQ(TestMissile4.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile4.getDrawPositionY(),10 - MISSILE_SPEED);
}

TEST(Missile, movesBackwardsCorrectly)
{
    float rotation = 0;
    Missile TestMissile1(10,10,rotation,p1_missile);
    TestMissile1.moveBackward();
    EXPECT_EQ(TestMissile1.getDrawPositionX(),10 - MISSILE_SPEED);
    EXPECT_EQ(TestMissile1.getDrawPositionY(),10);

    rotation = 90;
    Missile TestMissile2(10,10,rotation,p1_missile);
    TestMissile2.moveBackward();
    EXPECT_EQ(TestMissile2.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile2.getDrawPositionY(),10 - MISSILE_SPEED);

    rotation = 180;
    Missile TestMissile3(10,10,rotation,p1_missile);
    TestMissile3.moveBackward();
    EXPECT_EQ(TestMissile3.getDrawPositionX(),10 + MISSILE_SPEED);
    EXPECT_EQ(TestMissile3.getDrawPositionY(),10);

    rotation = 270;
    Missile TestMissile4(10,10,rotation,p1_missile);
    TestMissile4.moveBackward();
    EXPECT_EQ(TestMissile4.getDrawPositionX(),10);
    EXPECT_EQ(TestMissile4.getDrawPositionY(),10 + MISSILE_SPEED);
}

TEST(Missile, rotatesLeftAndRightCorrectly)
{
    Missile TestMissile1(10,10,0,p1_missile);
    TestMissile1.rotateLeft();
    EXPECT_EQ(TestMissile1.getDrawRotation(), 180);

    Missile TestMissile2(10,10,315,p1_missile);
    TestMissile2.rotateRight();
    EXPECT_EQ(TestMissile2.getDrawRotation(), 45);

    Missile TestMissile3(10,10,135,p1_missile);
    TestMissile3.rotateLeft();
    EXPECT_EQ(TestMissile3.getDrawRotation(), 45);

    Missile TestMissile4(10,10,170,p1_missile);
    TestMissile4.rotateLeft();
    EXPECT_EQ(TestMissile4.getDrawRotation(), 10);
}

TEST(Missile, booleanVariablesAreCorrectlySetAndRetrieved)
{
    Missile TestMissile1(10,10,0,p1_missile);

    TestMissile1.setBlocked(blocked);
    TestMissile1.setCollided();

    EXPECT_EQ(TestMissile1.isBlocked(), blocked);
    EXPECT_TRUE(TestMissile1.isDeleted());

    TestMissile1.setUnblocked();

    EXPECT_EQ(TestMissile1.isBlocked(), unblocked);
}

/*===================================================*/

///*================Tests for Barrier Class============*/

TEST(Barrier, ifInvalidCoOrdinatesThrowsException)
{
    EXPECT_THROW({Barrier TestBarrier(-10,10,barrier);},InvalidConstructorArgumentsBarrier);
    EXPECT_THROW({Barrier TestBarrier(10,-10,barrier);},InvalidConstructorArgumentsBarrier);
    EXPECT_NO_THROW({Barrier TestBarrier(10,10,barrier);});
    EXPECT_THROW({Barrier TestBarrier(10,10,p1_mine);},InvalidConstructorArgumentsBarrier);
}

TEST(Barrier, returnsCorrectEntityType)
{
    Barrier TestBarrier(10,10,barrier);

    EXPECT_EQ(TestBarrier.getType(),barrier);
}

TEST(Barrier, returnCorrectRectangleVertices)
{
    SpriteDimensions _dimensions;
    float origin_x = 100;
    float origin_y = 100;

    Barrier TestBarrier(origin_x,origin_y,barrier);
    rect_corners rect;

    rect.upper_left.x = origin_x - _dimensions.barrier_sprite_x/2;
    rect.upper_left.y = origin_y + _dimensions.barrier_sprite_y/2;
    rect.upper_right.x = origin_x + _dimensions.barrier_sprite_x/2;
    rect.upper_right.y = origin_y + _dimensions.barrier_sprite_y/2;
    rect.lower_left.x = origin_x - _dimensions.barrier_sprite_x/2;
    rect.lower_left.y = origin_y + _dimensions.barrier_sprite_y/2;
    rect.lower_right.x = origin_x + _dimensions.barrier_sprite_x/2;
    rect.lower_right.y = origin_y + _dimensions.barrier_sprite_y/2;

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
TEST(Mine,throwsExceptionIfInvalidCoordinatesGiven)
{
    double orign_x = 10;
    double origin_y = 10;
    EXPECT_THROW({Mine TestMine(-orign_x,origin_y,p1_mine);},InvalidConstructorArgumentsMine);
    EXPECT_THROW({Mine TestMine(orign_x,-origin_y,p1_mine);},InvalidConstructorArgumentsMine);
    EXPECT_NO_THROW({Mine TestMine(orign_x,origin_y, p1_mine);});
    EXPECT_THROW({Mine TestMine(orign_x,origin_y,p1_missile);},InvalidConstructorArgumentsMine);
}

TEST(Mine, returnsCorrectEntityType)
{
    Mine TestMine1(10,10,p1_mine);
    Mine TestMine2(10,10,p2_mine);

    EXPECT_EQ(TestMine1.getType(),p1_mine);
    EXPECT_EQ(TestMine2.getType(),p2_mine);
    EXPECT_NE(TestMine1.getType(),p2_mine);
}

TEST(Mine, booleanVariablesAreCorrectlySetAndRetrieved)
{
    Mine TestMine1(10,10,p1_mine);

    TestMine1.setCollided();

    EXPECT_TRUE(TestMine1.isDeleted());
}
///*===================================================*/


///*================Tests for Turret Class============*/

TEST(Turret,throwsExceptionIfInvalidCoordinatesGiven)
{
    double orign_x = 10;
    double origin_y = 10;
    double rotation = 10;
    EXPECT_ANY_THROW({Turret TestTurret(-orign_x,origin_y,rotation);});
    EXPECT_ANY_THROW({Turret TestTurret(orign_x,-origin_y, rotation);});
    EXPECT_NO_THROW({Turret TestTurret(orign_x,origin_y, rotation);});
    EXPECT_ANY_THROW({Turret TestTurret(orign_x,origin_y,-rotation);});
}

TEST(Turret, correctlyRotatesThroughCommand)
{
    double orign_x = 10;
    double origin_y = 10;
    double rotation = 2;
    double TurrRotationRate = -2;

    Turret testTurret1(orign_x,origin_y,rotation);

    EXPECT_EQ(testTurret1.getOrientation(), 2);

    testTurret1.rotateTurret();

    EXPECT_EQ(testTurret1.getOrientation(), 0);

    testTurret1.rotateTurret();

    EXPECT_NE(testTurret1.getOrientation(), 0);

}

///*===================================================*/



///*================Tests for GeometryEngine Class============*/


TEST(GeometryEngine, returnsTrueIfRectanglesCollided)
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
    rect_B.upper_right.y = 9.0;
    rect_B.lower_left.x = 2.0;
    rect_B.lower_left.y = 2.0;
    rect_B.lower_right.x = 6.0;
    rect_B.lower_right.y = 2.0;

    GeometryEngine CollisionTest;

    EXPECT_TRUE(CollisionTest.isCollision(rect_A, rect_B));
}

TEST(GeometryEngine, returnsFalseIfRectanglesAreNotCollided)
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

    rect_B.upper_left.x = 12.0;
    rect_B.upper_left.y = 19.0;
    rect_B.upper_right.x = 16.0;
    rect_B.upper_right.y = 19.0;
    rect_B.lower_left.x = 12.0;
    rect_B.lower_left.y = 12.0;
    rect_B.lower_right.x = 16.0;
    rect_B.lower_right.y = 12.0;

    GeometryEngine CollisionTest;

    EXPECT_FALSE(CollisionTest.isCollision(rect_A, rect_B));
}

TEST(GeometryEngine, returnsTrueIfOverlapOnAllAxes)
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

	coordinate axis;
	GeometryEngine CollisionTest;

	axis.x = rect_A.upper_right.x - rect_A.upper_left.x;
    axis.y = rect_A.upper_right.y - rect_A.upper_left.y;
    EXPECT_TRUE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));

    axis.x = rect_A.upper_right.x - rect_A.lower_right.x;
    axis.y = rect_A.upper_right.y - rect_A.lower_right.y;
    EXPECT_TRUE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));

    axis.x = rect_B.upper_left.x - rect_B.lower_left.x;
    axis.y = rect_B.upper_left.y - rect_B.lower_left.y;
    EXPECT_TRUE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));

    axis.x = rect_B.upper_left.x - rect_B.upper_right.x;
    axis.y = rect_B.upper_left.y - rect_B.upper_right.y;
    EXPECT_TRUE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));
}

TEST(GeometryEngine, returnsFalseIfNoOverlapOnAxisOne)
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

    rect_B.upper_left.x = 12.0;
    rect_B.upper_left.y = 19.0;
    rect_B.upper_right.x = 16.0;
    rect_B.upper_right.y = 19.0;
    rect_B.lower_left.x = 12.0;
    rect_B.lower_left.y = 12.0;
    rect_B.lower_right.x = 16.0;
    rect_B.lower_right.y = 12.0;

    coordinate axis;
    GeometryEngine CollisionTest;

    //Axis 1
    axis.x = rect_A.upper_right.x - rect_A.upper_left.x;
    axis.y = rect_A.upper_right.y - rect_A.upper_left.y;
    EXPECT_FALSE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));
}

TEST(GeometryEngine, returnsFalseIfNoOverlapOnAxisTwo)
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

    rect_B.upper_left.x = 12.0;
    rect_B.upper_left.y = 19.0;
    rect_B.upper_right.x = 16.0;
    rect_B.upper_right.y = 19.0;
    rect_B.lower_left.x = 12.0;
    rect_B.lower_left.y = 12.0;
    rect_B.lower_right.x = 16.0;
    rect_B.lower_right.y = 12.0;

    coordinate axis;
    GeometryEngine CollisionTest;

    //Axis 2
    axis.x = rect_A.upper_right.x - rect_A.lower_right.x;
    axis.y = rect_A.upper_right.y - rect_A.lower_right.y;
    EXPECT_FALSE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));
}

TEST(GeometryEngine, returnsFalseIfNoOverlapOnAxisThree)
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

    rect_B.upper_left.x = 12.0;
    rect_B.upper_left.y = 19.0;
    rect_B.upper_right.x = 16.0;
    rect_B.upper_right.y = 19.0;
    rect_B.lower_left.x = 12.0;
    rect_B.lower_left.y = 12.0;
    rect_B.lower_right.x = 16.0;
    rect_B.lower_right.y = 12.0;

    coordinate axis;
    GeometryEngine CollisionTest;

    //Axis 3
    axis.x = rect_B.upper_left.x - rect_B.lower_left.x;
    axis.y = rect_B.upper_left.y - rect_B.lower_left.y;
    EXPECT_FALSE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));
}

TEST(GeometryEngine, returnsFalseIfNoOverlapOnAxisFour)
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

    rect_B.upper_left.x = 12.0;
    rect_B.upper_left.y = 19.0;
    rect_B.upper_right.x = 16.0;
    rect_B.upper_right.y = 19.0;
    rect_B.lower_left.x = 12.0;
    rect_B.lower_left.y = 12.0;
    rect_B.lower_right.x = 16.0;
    rect_B.lower_right.y = 12.0;

    coordinate axis;
    GeometryEngine CollisionTest;

    //Axis 4
    axis.x = rect_B.upper_left.x - rect_B.upper_right.x;
    axis.y = rect_B.upper_left.y - rect_B.upper_right.y;
    EXPECT_FALSE(CollisionTest.isRectangleOverlapForAxis(axis, rect_A, rect_B));
}

TEST(GeometryEngine, returnsFalseIfTankNotInLineOfFireOfTurret)
{
    float rotation = 45.0;
    rect_corners shooter;
    rect_corners target;

    shooter.upper_left.x = 1.0;
    shooter.upper_left.y = 8.0;
    shooter.upper_right.x = 5.0;
    shooter.upper_right.y = 8.0;
    shooter.lower_left.x = 1.0;
    shooter.lower_left.y = 1.0;
    shooter.lower_right.x = 5.0;
    shooter.lower_right.y = 1.0;

    target.upper_left.x = 11.0;
    target.upper_left.y = 8.0;
    target.upper_right.x = 15.0;
    target.upper_right.y = 8.0;
    target.lower_left.x = 11.0;
    target.lower_left.y = 1.0;
    target.lower_right.x = 15.0;
    target.lower_right.y = 1.0;

    GeometryEngine lineOfFireTest;

    EXPECT_FALSE(lineOfFireTest.isInLineOfFire(rotation, shooter, target, 4, 4));
}

TEST(GeometryEngine, correctlyIdentifiesRelativePositionsOfBoundingBoxes_Above)
{
    rect_corners entity;
    rect_corners relative_entity;

    //Set box
    relative_entity.upper_left.x = 100.0;
    relative_entity.upper_left.y = 100.0;
    relative_entity.upper_right.x = 200.0;
    relative_entity.upper_right.y = 100.0;
    relative_entity.lower_left.x = 100.0;
    relative_entity.lower_left.y = 50.0;
    relative_entity.lower_right.x = 200.0;
    relative_entity.lower_right.y = 50.0;

    //Entity Above box
    entity.upper_left.x = 110.0;
    entity.upper_left.y = 110.0;
    entity.upper_right.x = 120.0;
    entity.upper_right.y = 110.0;
    entity.lower_left.x = 110.0;
    entity.lower_left.y = 90.0;
    entity.lower_right.x = 120.0;
    entity.lower_right.y = 90.0;

    GeometryEngine relativePositionTest;

    EXPECT_EQ(relativePositionTest.getRelativePosition(entity,relative_entity), blocked_vertically);
    EXPECT_EQ(relativePositionTest.getRelativePosition(entity,relative_entity), blocked_vertically);
}

TEST(GeometryEngine, correctlyIdentifiesRelativePositionsOfBoundingBoxes_Below)
{
    rect_corners entity;
    rect_corners relative_entity;

    //Set box
    relative_entity.upper_left.x = 100.0;
    relative_entity.upper_left.y = 100.0;
    relative_entity.upper_right.x = 200.0;
    relative_entity.upper_right.y = 100.0;
    relative_entity.lower_left.x = 100.0;
    relative_entity.lower_left.y = 50.0;
    relative_entity.lower_right.x = 200.0;
    relative_entity.lower_right.y = 50.0;

    //Entity Below box
    entity.upper_left.x = 110.0;
    entity.upper_left.y = 60.0;
    entity.upper_right.x = 120.0;
    entity.upper_right.y = 60.0;
    entity.lower_left.x = 110.0;
    entity.lower_left.y = 30.0;
    entity.lower_right.x = 120.0;
    entity.lower_right.y = 30.0;

    GeometryEngine relativePositionTest;

    EXPECT_EQ(relativePositionTest.getRelativePosition(entity,relative_entity), blocked_vertically);
}

TEST(GeometryEngine, correctlyIdentifiesRelativePositionsOfBoundingBoxes_Left)
{
    rect_corners entity;
    rect_corners relative_entity;

    //Set box
    relative_entity.upper_left.x = 100.0;
    relative_entity.upper_left.y = 100.0;
    relative_entity.upper_right.x = 200.0;
    relative_entity.upper_right.y = 100.0;
    relative_entity.lower_left.x = 100.0;
    relative_entity.lower_left.y = 50.0;
    relative_entity.lower_right.x = 200.0;
    relative_entity.lower_right.y = 50.0;

    //Entity left of box
    entity.upper_left.x = 80.0;
    entity.upper_left.y = 90.0;
    entity.upper_right.x = 110.0;
    entity.upper_right.y = 90.0;
    entity.lower_left.x = 80.0;
    entity.lower_left.y = 60.0;
    entity.lower_right.x = 110.0;
    entity.lower_right.y = 60.0;

    GeometryEngine relativePositionTest;

    EXPECT_EQ(relativePositionTest.getRelativePosition(entity,relative_entity), blocked_horizontally);
}

TEST(GeometryEngine, correctlyIdentifiesRelativePositionsOfBoundingBoxes_Right)
{
    rect_corners entity;
    rect_corners relative_entity;

    //Set box
    relative_entity.upper_left.x = 100.0;
    relative_entity.upper_left.y = 100.0;
    relative_entity.upper_right.x = 200.0;
    relative_entity.upper_right.y = 100.0;
    relative_entity.lower_left.x = 100.0;
    relative_entity.lower_left.y = 50.0;
    relative_entity.lower_right.x = 200.0;
    relative_entity.lower_right.y = 50.0;

    //Entity left of box
    entity.upper_left.x = 190.0;
    entity.upper_left.y = 90.0;
    entity.upper_right.x = 230.0;
    entity.upper_right.y = 90.0;
    entity.lower_left.x = 190.0;
    entity.lower_left.y = 60.0;
    entity.lower_right.x = 230.0;
    entity.lower_right.y = 60.0;

    GeometryEngine relativePositionTest;

    EXPECT_EQ(relativePositionTest.getRelativePosition(entity,relative_entity), blocked_horizontally);
}

TEST(GeometryEngine, throwsExceptionIfInvalidRectEntityPassed)
{
    rect_corners entity;
    rect_corners relative_entity;

    relative_entity.upper_left.x = -200.0;
    relative_entity.upper_left.y = 100.0;
    relative_entity.upper_right.x = 200.0;
    relative_entity.upper_right.y = 100.0;
    relative_entity.lower_left.x = 100.0;
    relative_entity.lower_left.y = 50.0;
    relative_entity.lower_right.x = 200.0;
    relative_entity.lower_right.y = 50.0;

    entity.upper_left.x = 110.0;
    entity.upper_left.y = 60.0;
    entity.upper_right.x = 120.0;
    entity.upper_right.y = 60.0;
    entity.lower_left.x = 110.0;
    entity.lower_left.y = 30.0;
    entity.lower_right.x = 120.0;
    entity.lower_right.y = 30.0;

    GeometryEngine geometryTest;

    EXPECT_THROW({geometryTest.isCollision(entity,relative_entity);}, InvalidRectEntityProvided);

    relative_entity.upper_left.x = 100.0;

    EXPECT_NO_THROW({geometryTest.isCollision(entity,relative_entity);});
}

TEST(GeometryEngine, returnsTrueIfTankInLineOfFire)
{
    float rotation = 0.0;
    float shooter_y = 10.0;
    float target_y = 12.0;
    rect_corners shooter;
    rect_corners target;

    target.upper_left.x = 16.0;
    target.upper_left.y = 14.0;
    target.upper_right.x = 18.0;
    target.upper_right.y = 12.0;
    target.lower_left.x = 14.0;
    target.lower_left.y = 12.0;
    target.lower_right.x = 16.0;
    target.lower_right.y = 10.0;

    shooter.upper_left.x = 9.0;
    shooter.upper_left.y = 11.0;
    shooter.upper_right.x = 11.0;
    shooter.upper_right.y = 11.0;
    shooter.lower_left.x = 9.0;
    shooter.lower_left.y = 9.0;
    shooter.lower_right.x = 11.0;
    shooter.lower_right.y = 9.0;

    GeometryEngine lineOfFireTest;

    EXPECT_TRUE(lineOfFireTest.isInLineOfFire(rotation, shooter, target, shooter_y, target_y));
}

TEST(GeometryEngine, returnsTrueIfTankNotInLineOfFire)
{
    float rotation = 45.0;
    float shooter_y = 10.0;
    float target_y = 12.0;
    rect_corners shooter;
    rect_corners target;

    target.upper_left.x = 16.0;
    target.upper_left.y = 14.0;
    target.upper_right.x = 18.0;
    target.upper_right.y = 12.0;
    target.lower_left.x = 14.0;
    target.lower_left.y = 12.0;
    target.lower_right.x = 16.0;
    target.lower_right.y = 10.0;

    shooter.upper_left.x = 10.0;
    shooter.upper_left.y = 12.0;
    shooter.upper_right.x = 12.0;
    shooter.upper_right.y = 10.0;
    shooter.lower_left.x = 8.0;
    shooter.lower_left.y = 10.0;
    shooter.lower_right.x = 10.0;
    shooter.lower_right.y = 8.0;

    GeometryEngine lineOfFireTest;

    EXPECT_FALSE(lineOfFireTest.isInLineOfFire(rotation, shooter, target, shooter_y, target_y));
}

TEST(GeometryEngine, returnsFalseIfTankBehindTurretAndNotInLineOfFire)
{
    float rotation = 135.0;
    float shooter_y = 10.0;
    float target_y = 9.5;
    rect_corners shooter;
    rect_corners target;

    target.upper_left.x = 12.0;
    target.upper_left.y = 10.0;
    target.upper_right.x = 13.0;
    target.upper_right.y = 10.0;
    target.lower_left.x = 12.0;
    target.lower_left.y = 9.0;
    target.lower_right.x = 13.0;
    target.lower_right.y = 9.0;

    shooter.upper_left.x = 8.0;
    shooter.upper_left.y = 12.0;
    shooter.upper_right.x = 12.0;
    shooter.upper_right.y = 12.0;
    shooter.lower_left.x = 8.0;
    shooter.lower_left.y = 8.0;
    shooter.lower_right.x = 12.0;
    shooter.lower_right.y = 8.0;

    GeometryEngine lineOfFireTest;

    EXPECT_FALSE(lineOfFireTest.isInLineOfFire(rotation, shooter, target, shooter_y, target_y));
}

TEST(GeometryEngine, returnsFalseIfTankBehindTurretWithSameOriginAndNotInLineOfFire)
{
    float rotation = 180.0;
    float shooter_y = 10.0;
    float target_y = 10.0;
    rect_corners shooter;
    rect_corners target;

    shooter.upper_left.x = 12.0;
    shooter.upper_left.y = 11.0;
    shooter.upper_right.x = 14.0;
    shooter.upper_right.y = 11.0;
    shooter.lower_left.x = 12.0;
    shooter.lower_left.y = 9.0;
    shooter.lower_right.x = 14.0;
    shooter.lower_right.y = 9.0;

    shooter.upper_left.x = 9.0;
    shooter.upper_left.y = 11.0;
    shooter.upper_right.x = 11.0;
    shooter.upper_right.y = 11.0;
    shooter.lower_left.x = 9.0;
    shooter.lower_left.y = 9.0;
    shooter.lower_right.x = 11.0;
    shooter.lower_right.y = 9.0;

    GeometryEngine lineOfFireTest;

    EXPECT_FALSE(lineOfFireTest.isInLineOfFire(rotation, shooter, target, shooter_y, target_y));
}

TEST(GeometryEngine, calculatesCorrectVectorLength)
{
    float x_coord_1 = 1.0;
    float y_coord_1 = 4.0;
    float x_coord_2 = 1.0;
    float y_coord_2 = 2.0;

    GeometryEngine test;

    float test_ans = test.calculateVectorLength(x_coord_1, y_coord_1, x_coord_2, y_coord_2);

    EXPECT_EQ(test_ans, 2.0);
}

///*===================================================*/


///*================Tests for TrackingManager Class============*/

TEST(TrackingManager, correctlyTracksTankEntityForP1)
{
    TrackingManager trackingManager;
    GameManagementData data;

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p1_tank));

    std::weak_ptr<Trackable> tank_track_wp = std::dynamic_pointer_cast<Trackable>(tank_del_sp);
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);

    trackingManager.addNewEntity(tank_track_wp);
    trackingManager.manage(data);

    EXPECT_EQ(trackingManager.getP1PositionX(), 30);
    EXPECT_EQ(trackingManager.getP1PositionY(), 30);
    EXPECT_EQ(trackingManager.getP1Rotation(), 0);

    tank_mov_sp->moveForward();
    trackingManager.manage(data);

    EXPECT_EQ(trackingManager.getP1PositionX(), 30 + TANK_SPEED);
    EXPECT_EQ(trackingManager.getP1PositionY(), 30);
    EXPECT_EQ(trackingManager.getP1Rotation(), 0);

    tank_mov_sp->moveForward();
    trackingManager.manage(data);

    EXPECT_NE(trackingManager.getP1PositionX(), 30 + TANK_SPEED);
}

TEST(TrackingManager, correctlyTracksTankEntityForP2)
{
    TrackingManager trackingManager;
    GameManagementData data;

    std::shared_ptr<Deletable> tank_del_sp(new Tank(40,40,0,p2_tank));

    std::weak_ptr<Trackable> tank_track_wp = std::dynamic_pointer_cast<Trackable>(tank_del_sp);
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);

    trackingManager.addNewEntity(tank_track_wp);
    trackingManager.manage(data);

    EXPECT_EQ(trackingManager.getP2PositionX(), 40);
    EXPECT_EQ(trackingManager.getP2PositionY(), 40);
    EXPECT_EQ(trackingManager.getP2Rotation(), 0);

    tank_mov_sp->moveForward();
    trackingManager.manage(data);

    EXPECT_EQ(trackingManager.getP2PositionX(), 40 + TANK_SPEED);
    EXPECT_EQ(trackingManager.getP2PositionY(), 40);
    EXPECT_EQ(trackingManager.getP2Rotation(), 0);

    tank_mov_sp->moveForward();
    trackingManager.manage(data);

    EXPECT_NE(trackingManager.getP2PositionX(), 30 + TANK_SPEED);
}


TEST(TrackingManager, correctlyTracksTurretEntity)
{
    TrackingManager trackingManager;
    GameManagementData data;

    std::shared_ptr<Deletable> turret_del_sp(new Turret(40,40,0));

    std::weak_ptr<Trackable> turret_track_wp = std::dynamic_pointer_cast<Trackable>(turret_del_sp);

    trackingManager.addNewEntity(turret_track_wp);

    trackingManager.manage(data);

    const std::vector<float>& turretVectorX = trackingManager.getTurretPositionsX();
    const std::vector<float>& turretVectorY = trackingManager.getTurretPositionsY();

//    auto turrXPosIt = turretVectorX.begin();
//    float turrXPos = *turrXPosIt;
//    float turrYPos = turretVectorY[0];

//    EXPECT_EQ(turrXPos, 1);
//    EXPECT_EQ(turrXPos, 40);
//    EXPECT_EQ(turrYPos, 40);

    //Test not finnished as gtest seems that it cannot handle vectors - due to its use of malloc perhaps?
}

TEST(TrackingManager, enablesTurretFireWhenTankAndTurretAreInRange)
{
    TrackingManager trackingManager;
    GameManagementData data;
    data.resetActionsInfo();
    actions_info testActions = data.giveActionInfo();
    EXPECT_EQ(testActions.turret_fire, false);

    //Add a Turret to the manager
    std::shared_ptr<Deletable> turret_del_sp(new Turret(550,100,358));
    std::weak_ptr<Trackable> turret_track_wp = std::dynamic_pointer_cast<Trackable>(turret_del_sp);
    trackingManager.addNewEntity(turret_track_wp);

    //Add Tank to the manager
    std::shared_ptr<Deletable> tank_del_sp(new Tank(850,350,0,p1_tank));
    std::weak_ptr<Trackable> tank_track_wp = std::dynamic_pointer_cast<Trackable>(tank_del_sp);
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);
    trackingManager.addNewEntity(tank_track_wp);

    tank_mov_sp->moveForward();
    trackingManager.manage(data);

    testActions = data.giveActionInfo();
    EXPECT_EQ(testActions.turret_fire, false);

    tank_mov_sp->moveForward();
    trackingManager.manage(data);

    testActions = data.giveActionInfo();
    EXPECT_EQ(testActions.turret_fire, false);
}

///*===================================================*/


///*================Tests for MoveManager Class============*/
TEST(MoveManager, correctlyMovesTankEntityForP1)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p1_tank));
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);
    std::shared_ptr<Trackable> tank_track_sp = std::dynamic_pointer_cast<Trackable>(tank_del_sp);

    moveManager.addNewEntity(tank_mov_sp);

    moveManager.manage(data);
    EXPECT_NE(tank_track_sp->getPositionX(), 30 + TANK_SPEED);

    data.moveForwardP1();
    moveManager.manage(data);

    EXPECT_EQ(tank_track_sp->getPositionX(), 30 + TANK_SPEED);
    EXPECT_NE(tank_track_sp->getPositionY(), 30 + TANK_SPEED);
}

TEST(MoveManager, correctlyMovesTankEntityForP2)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p2_tank));
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);
    std::shared_ptr<Trackable> tank_track_sp = std::dynamic_pointer_cast<Trackable>(tank_del_sp);

    moveManager.addNewEntity(tank_mov_sp);

    moveManager.manage(data);
    EXPECT_NE(tank_track_sp->getPositionX(), 30 + TANK_SPEED);

    data.moveForwardP2();
    moveManager.manage(data);

    EXPECT_EQ(tank_track_sp->getPositionX(), 30 + TANK_SPEED);
    EXPECT_NE(tank_track_sp->getPositionY(), 30 + TANK_SPEED);
}

TEST(MoveManager, correctlyMovesMissileEntityForP1)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> missile_del_sp(new Missile(30,30,0,p1_missile));
    std::shared_ptr<Movable> missile_mov_sp = std::dynamic_pointer_cast<Movable>(missile_del_sp);

    moveManager.addNewEntity(missile_mov_sp);

    moveManager.manage(data);
    EXPECT_EQ(missile_del_sp->getDrawPositionX(), 30 + MISSILE_SPEED);
    EXPECT_NE(missile_del_sp->getDrawPositionY(), 30 + MISSILE_SPEED);

    moveManager.manage(data);
    moveManager.manage(data);
    moveManager.manage(data);

    EXPECT_EQ(missile_del_sp->getDrawPositionX(), 30 + 4*MISSILE_SPEED);
    EXPECT_EQ(missile_del_sp->getDrawPositionY(), 30);
}

TEST(MoveManager, correctlyMovesMissileEntityForP2)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> missile_del_sp(new Missile(30,30,0,p2_missile));
    std::shared_ptr<Movable> missile_mov_sp = std::dynamic_pointer_cast<Movable>(missile_del_sp);

    moveManager.addNewEntity(missile_mov_sp);

    moveManager.manage(data);
    EXPECT_EQ(missile_del_sp->getDrawPositionX(), 30 + MISSILE_SPEED);
    EXPECT_NE(missile_del_sp->getDrawPositionY(), 30 + MISSILE_SPEED);

    moveManager.manage(data);
    moveManager.manage(data);
    moveManager.manage(data);

    EXPECT_EQ(missile_del_sp->getDrawPositionX(), 30 + 4*MISSILE_SPEED);
    EXPECT_EQ(missile_del_sp->getDrawPositionY(), 30);
}

TEST(MoveManager, doesNotMoveTankIfBlocked_P1)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p1_tank));
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);
    std::shared_ptr<Collidable> tank_collide_sp = std::dynamic_pointer_cast<Collidable>(tank_del_sp);

    moveManager.addNewEntity(tank_mov_sp);
    tank_collide_sp->setBlocked(blocked);

    moveManager.manage(data);

    EXPECT_NE(tank_del_sp->getDrawPositionX(), 30 + MISSILE_SPEED);
    EXPECT_EQ(tank_del_sp->getDrawPositionY(), 30);

    moveManager.manage(data);
    moveManager.manage(data);
    moveManager.manage(data);

    EXPECT_EQ(tank_del_sp->getDrawPositionX(), 30);
    EXPECT_EQ(tank_del_sp->getDrawPositionY(), 30);
}

TEST(MoveManager, doesNotMoveTankIfBlocked_P2)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p2_tank));
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);
    std::shared_ptr<Collidable> tank_collide_sp = std::dynamic_pointer_cast<Collidable>(tank_del_sp);

    moveManager.addNewEntity(tank_mov_sp);
    tank_collide_sp->setBlocked(blocked);

    moveManager.manage(data);

    EXPECT_NE(tank_del_sp->getDrawPositionX(), 30 + MISSILE_SPEED);
    EXPECT_EQ(tank_del_sp->getDrawPositionY(), 30);

    moveManager.manage(data);
    moveManager.manage(data);
    moveManager.manage(data);

    EXPECT_EQ(tank_del_sp->getDrawPositionX(), 30);
    EXPECT_EQ(tank_del_sp->getDrawPositionY(), 30);
}

TEST(MoveManager, missileReflectsCorrectlyIfBlockedHorizontally)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> missile_del_sp(new Missile(30,30,0,p1_missile));
    std::shared_ptr<Movable> missile_mov_sp = std::dynamic_pointer_cast<Movable>(missile_del_sp);
    std::shared_ptr<Collidable> missile_collide_sp = std::dynamic_pointer_cast<Collidable>(missile_del_sp);

    moveManager.addNewEntity(missile_mov_sp);
    missile_collide_sp->setBlocked(blocked_horizontally);

    moveManager.manage(data);
    EXPECT_EQ(missile_del_sp->getDrawRotation(), 180);
    EXPECT_EQ(missile_del_sp->getDrawPositionX(), 30 - MISSILE_SPEED);

    moveManager.manage(data);
    EXPECT_EQ(missile_del_sp->getDrawRotation(), 0);
    EXPECT_EQ(missile_del_sp->getDrawPositionX(), 30);
}

TEST(MoveManager, missileReflectsCorrectlyIfBlockedVertically)
{
    MoveManager moveManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> missile_del_sp(new Missile(30,30,90,p1_missile));
    std::shared_ptr<Movable> missile_mov_sp = std::dynamic_pointer_cast<Movable>(missile_del_sp);
    std::shared_ptr<Collidable> missile_collide_sp = std::dynamic_pointer_cast<Collidable>(missile_del_sp);

    moveManager.addNewEntity(missile_mov_sp);
    missile_collide_sp->setBlocked(blocked_vertically);

    moveManager.manage(data);
    EXPECT_EQ(missile_del_sp->getDrawRotation(), 270);
    EXPECT_EQ(missile_del_sp->getDrawPositionY(), 30 - MISSILE_SPEED);

    moveManager.manage(data);
    EXPECT_EQ(missile_del_sp->getDrawRotation(), 90);
    EXPECT_EQ(missile_del_sp->getDrawPositionY(), 30);
}
///*===================================================*/


///*================Tests for DestructionManager Class============*/

TEST(DestructionManager, correctlyDeletesTankEntityFromGame)
{
    DestructionManager destructionManager;
    GameManagementData data;


    std::shared_ptr<Deletable> tank1_del_sp(new Tank(10,10,0,p1_tank));
    std::shared_ptr<Collidable> tank1_collide_sp = std::dynamic_pointer_cast<Collidable>(tank1_del_sp);
    std::shared_ptr<Deletable> tank2_del_sp(new Tank(10,10,0,p2_tank));
    std::shared_ptr<Collidable> tank2_collide_sp = std::dynamic_pointer_cast<Collidable>(tank2_del_sp);

    destructionManager.addNewEntity(tank1_del_sp);
    destructionManager.addNewEntity(tank2_del_sp);
    //Check number of shared pointers for each entity - this should be 3 now
    EXPECT_EQ(tank1_del_sp.use_count(), 3);
    EXPECT_EQ(tank2_del_sp.use_count(), 3);

    tank1_collide_sp->setCollided();
    tank2_collide_sp->setCollided();
    destructionManager.manage(data);

    //Check number of shared pointers for each entity - this should be 2 now
    EXPECT_EQ(tank1_del_sp.use_count(), 2);
    EXPECT_EQ(tank2_del_sp.use_count(), 2);
}

TEST(DestructionManager, correctlyDeletesMissileEntityFromGame)
{
    DestructionManager destructionManager;
    GameManagementData data;


    std::shared_ptr<Deletable> missile1_del_sp(new Missile(10,10,0,p1_missile));
    std::shared_ptr<Collidable> missile1_collide_sp = std::dynamic_pointer_cast<Collidable>(missile1_del_sp);
    std::shared_ptr<Deletable> missile2_del_sp(new Missile(10,10,0,p2_missile));
    std::shared_ptr<Collidable> missile2_collide_sp = std::dynamic_pointer_cast<Collidable>(missile2_del_sp);

    destructionManager.addNewEntity(missile1_del_sp);
    destructionManager.addNewEntity(missile2_del_sp);
    //Check number of shared pointers for each entity - this should be 3 now
    EXPECT_EQ(missile1_del_sp.use_count(), 3);
    EXPECT_EQ(missile2_del_sp.use_count(), 3);

    missile1_collide_sp->setCollided();
    missile2_collide_sp->setCollided();
    destructionManager.manage(data);

    //Check number of shared pointers for each entity - this should be 2 now
    EXPECT_EQ(missile1_del_sp.use_count(), 2);
    EXPECT_EQ(missile2_del_sp.use_count(), 2);
}

TEST(DestructionManager, correctlyDeletesMineEntityFromGame)
{
    DestructionManager destructionManager;
    GameManagementData data;


    std::shared_ptr<Deletable> mine1_del_sp(new Mine(10,10,p1_mine));
    std::shared_ptr<Collidable> mine1_collide_sp = std::dynamic_pointer_cast<Collidable>(mine1_del_sp);
    std::shared_ptr<Deletable> mine2_del_sp(new Mine(10,10,p2_mine));
    std::shared_ptr<Collidable> mine2_collide_sp = std::dynamic_pointer_cast<Collidable>(mine2_del_sp);

    destructionManager.addNewEntity(mine1_del_sp);
    destructionManager.addNewEntity(mine2_del_sp);
    //Check number of shared pointers for each entity - this should be 3 now
    EXPECT_EQ(mine1_del_sp.use_count(), 3);
    EXPECT_EQ(mine2_del_sp.use_count(), 3);

    mine1_collide_sp->setCollided();
    mine2_collide_sp->setCollided();
    destructionManager.manage(data);

    //Check number of shared pointers for each entity - this should be 2 now
    EXPECT_EQ(mine1_del_sp.use_count(), 2);
    EXPECT_EQ(mine2_del_sp.use_count(), 2);
}

TEST(DestructionManager, correctlyDeletesTurretEntityFromGame)
{
    DestructionManager destructionManager;
    GameManagementData data;


    std::shared_ptr<Deletable> turret_del_sp(new Turret(10,10,0));
    std::shared_ptr<Collidable> turret_collide_sp = std::dynamic_pointer_cast<Collidable>(turret_del_sp);

    destructionManager.addNewEntity(turret_del_sp);

    //Check number of shared pointers for each entity - this should be 3 now
    EXPECT_EQ(turret_del_sp.use_count(), 3);

    turret_collide_sp->setCollided();
    destructionManager.manage(data);

    //Check number of shared pointers for each entity - this should be 2 now
    EXPECT_EQ(turret_del_sp.use_count(), 2);
}

TEST(DestructionManager, correctlyIncreasesPlayerScoresUponTheirDeath)
{
    DestructionManager destructionManager;
    GameManagementData data;
    data.resetActionsInfo();

    std::shared_ptr<Deletable> tank1_del_sp(new Tank(10,10,0,p1_tank));
    std::shared_ptr<Collidable> tank1_collide_sp = std::dynamic_pointer_cast<Collidable>(tank1_del_sp);
    std::shared_ptr<Deletable> tank2_del_sp(new Tank(10,10,0,p2_tank));
    std::shared_ptr<Collidable> tank2_collide_sp = std::dynamic_pointer_cast<Collidable>(tank2_del_sp);

    destructionManager.addNewEntity(tank1_del_sp);
    destructionManager.addNewEntity(tank2_del_sp);
    //Check number of shared pointers for each entity - this should be 3 now
    EXPECT_EQ(data.getP1Score(), 0);
    EXPECT_EQ(data.getP2Score(), 0);

    tank1_collide_sp->setCollided();
    tank2_collide_sp->setCollided();
    destructionManager.manage(data);

    //Check number of shared pointers for each entity - this should be 2 now
    EXPECT_EQ(data.getP1Score(), 1);
    EXPECT_EQ(data.getP2Score(), 1);
}
///*==============================================================*/


///*================Tests for StateManager Class============*/
TEST(GameStateManager, doesNotAllowCreationOfMissileBeforeTimerExpiers)
{
    GameStateManager gameMan;
    GameManagementData data;
    data.missileFiredP1();
    data.missileFiredP2();

    gameMan.manage(data);

    actions_info actionsBox = data.giveActionInfo();

    EXPECT_EQ(actionsBox.attack_1, fire_missile);
    EXPECT_EQ(actionsBox.attack_2, fire_missile);

    gameMan.manage(data);

    actionsBox = data.giveActionInfo();

    EXPECT_EQ(actionsBox.attack_1, do_nothing);
    EXPECT_EQ(actionsBox.attack_2, do_nothing);
}

TEST(GameStateManager, doesNotAllowCreationOfMineBeforeTimerExpiers)
{
    GameStateManager gameMan;
    GameManagementData data;
    data.mineLaidP1();
    data.mineLaidP2();

    gameMan.manage(data);

    actions_info actionsBox = data.giveActionInfo();

    EXPECT_EQ(actionsBox.attack_1, lay_mine);
    EXPECT_EQ(actionsBox.attack_2, lay_mine);

    gameMan.manage(data);

    actionsBox = data.giveActionInfo();

    EXPECT_EQ(actionsBox.attack_1, do_nothing);
    EXPECT_EQ(actionsBox.attack_2, do_nothing);
}

///*==============================================================*/


///*================Tests for TurretManager Class============*/

TEST(TurretManager, CorrectlyRotatesTurretEntity)
{
    TurretManager turManager;

    std::shared_ptr<Deletable> turret_del_sp(new Turret(30,30,2));
    std::weak_ptr<Turret> turret_tur_sp = std::dynamic_pointer_cast<Turret>(turret_del_sp);

    turManager.addNewEntity(turret_tur_sp);
    EXPECT_EQ(turret_del_sp->getDrawRotation(), 2);

    turManager.manage();
    EXPECT_EQ(turret_del_sp->getDrawRotation(), 2 + TURRET_ROTATION_SPEED);

    turManager.manage();
    turManager.manage();
    turManager.manage();

    EXPECT_EQ(turret_del_sp->getDrawRotation(), 360 + 3*TURRET_ROTATION_SPEED);
}

///*==============================================================*/


///*================Tests for CollisioniManager Class============*/
TEST(CollisionManager, correctlyBlocksTanksAndBarriers)
{
    CollisionManager colisionManager;

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p1_tank));
    std::shared_ptr<Collidable> tank_collide_sp = std::dynamic_pointer_cast<Collidable>(tank_del_sp);
    std::shared_ptr<Movable> tank_mov_sp = std::dynamic_pointer_cast<Movable>(tank_del_sp);

    colisionManager.addNewEntity(tank_collide_sp);

    std::shared_ptr<Deletable> barrier_del_sp(new Barrier(50,50,barrier));
    std::shared_ptr<Collidable> barrier_collide_sp = std::dynamic_pointer_cast<Collidable>(barrier_del_sp);
    std::shared_ptr<Movable> barrier_mov_sp = std::dynamic_pointer_cast<Movable>(barrier_del_sp);

    colisionManager.addNewEntity(barrier_collide_sp);

    EXPECT_EQ(tank_mov_sp->isBlocked(), unblocked);

    colisionManager.manage();

    EXPECT_EQ(tank_mov_sp->isBlocked(), blocked);
}

TEST(CollisionManager, correctlyBlocksTanksAndTanks)
{
    CollisionManager colisionManager;

    std::shared_ptr<Deletable> tank1_del_sp(new Tank(30,30,0,p1_tank));
    std::shared_ptr<Collidable> tank1_collide_sp = std::dynamic_pointer_cast<Collidable>(tank1_del_sp);
    std::shared_ptr<Movable> tank1_mov_sp = std::dynamic_pointer_cast<Movable>(tank1_del_sp);

    colisionManager.addNewEntity(tank1_collide_sp);

    std::shared_ptr<Deletable> tank2_del_sp(new Tank(50,50,0,p2_tank));
    std::shared_ptr<Collidable> tank2_collide_sp = std::dynamic_pointer_cast<Collidable>(tank2_del_sp);
    std::shared_ptr<Movable> tank2_mov_sp = std::dynamic_pointer_cast<Movable>(tank2_del_sp);

    colisionManager.addNewEntity(tank2_collide_sp);

    EXPECT_EQ(tank1_mov_sp->isBlocked(), unblocked);
    EXPECT_EQ(tank2_mov_sp->isBlocked(), unblocked);

    colisionManager.manage();

    EXPECT_EQ(tank2_mov_sp->isBlocked(), blocked);
    EXPECT_EQ(tank1_mov_sp->isBlocked(), blocked);
}

TEST(CollisionManager, correctlyBlocksMissilesAndBarriers)
{
    CollisionManager colisionManager;

    std::shared_ptr<Deletable> missile_del_sp(new Missile(48,48,0,p1_missile));
    std::shared_ptr<Collidable> missile_collide_sp = std::dynamic_pointer_cast<Collidable>(missile_del_sp);
    std::shared_ptr<Movable> missile_mov_sp = std::dynamic_pointer_cast<Movable>(missile_del_sp);

    colisionManager.addNewEntity(missile_collide_sp);

    std::shared_ptr<Deletable> barrier_del_sp(new Barrier(50,50,barrier));
    std::shared_ptr<Collidable> barrier_collide_sp = std::dynamic_pointer_cast<Collidable>(barrier_del_sp);
    std::shared_ptr<Movable> barrier_mov_sp = std::dynamic_pointer_cast<Movable>(barrier_del_sp);

    colisionManager.addNewEntity(barrier_collide_sp);

    EXPECT_EQ(missile_mov_sp->isBlocked(), unblocked);

    colisionManager.manage();

    EXPECT_EQ(missile_mov_sp->isBlocked(), unblocked);
}

TEST(CollisionManager, indicatesCollisionHasTakenPlace)
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

    GeometryEngine collision_helper;

    EXPECT_TRUE(collision_helper.isCollision(rect_A, rect_B));
}

TEST(CollisionManager, correctlyCollidesTanksAndMissiles)
{
    CollisionManager colisionManager;

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p1_tank));
    std::shared_ptr<Collidable> tank_collide_sp = std::dynamic_pointer_cast<Collidable>(tank_del_sp);

    colisionManager.addNewEntity(tank_collide_sp);

    std::shared_ptr<Deletable> missile_del_sp(new Missile(50,50, 0 , p2_missile));
    std::shared_ptr<Collidable> missile_collide_sp = std::dynamic_pointer_cast<Collidable>(missile_del_sp);

    colisionManager.addNewEntity(missile_collide_sp);

    EXPECT_FALSE(tank_del_sp->isDeleted());
    EXPECT_FALSE(missile_del_sp->isDeleted());

    colisionManager.manage();

    EXPECT_TRUE(tank_del_sp->isDeleted());
    EXPECT_TRUE(missile_del_sp->isDeleted());
}

TEST(CollisionManager, correctlyCollidesMissilesAndMissiles)
{
    CollisionManager colisionManager;

    std::shared_ptr<Deletable> missile1_del_sp(new Missile(49,49,0,p1_missile));
    std::shared_ptr<Collidable> missile1_collide_sp = std::dynamic_pointer_cast<Collidable>(missile1_del_sp);

    colisionManager.addNewEntity(missile1_collide_sp);

    std::shared_ptr<Deletable> missile2_del_sp(new Missile(50,50, 0 , p2_missile));
    std::shared_ptr<Collidable> missile2_collide_sp = std::dynamic_pointer_cast<Collidable>(missile2_del_sp);

    colisionManager.addNewEntity(missile2_collide_sp);

    EXPECT_FALSE(missile1_del_sp->isDeleted());
    EXPECT_FALSE(missile2_del_sp->isDeleted());

    colisionManager.manage();

    EXPECT_TRUE(missile1_del_sp->isDeleted());
    EXPECT_TRUE(missile2_del_sp->isDeleted());
}

TEST(CollisionManager, correctlyCollidesTanksAndMines)
{
    CollisionManager colisionManager;

    std::shared_ptr<Deletable> tank_del_sp(new Tank(30,30,0,p1_tank));
    std::shared_ptr<Collidable> tank_collide_sp = std::dynamic_pointer_cast<Collidable>(tank_del_sp);

    colisionManager.addNewEntity(tank_collide_sp);

    std::shared_ptr<Deletable> mine_del_sp(new Mine(50,50,p2_mine));
    std::shared_ptr<Collidable> mine_collide_sp = std::dynamic_pointer_cast<Collidable>(mine_del_sp);

    colisionManager.addNewEntity(mine_collide_sp);

    EXPECT_FALSE(tank_del_sp->isDeleted());
    EXPECT_FALSE(mine_del_sp->isDeleted());

    colisionManager.manage();

    EXPECT_TRUE(tank_del_sp->isDeleted());
    EXPECT_TRUE(mine_del_sp->isDeleted());
}

///*==============================================================*/


