/**
 * \file 	ClassTests.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	18 September 2014
 * \brief 	Unit tests for all classes. Included in single file for regression testing purposes.
 */

#include "Manager.h"
#include "CollisionManager.h"
#include <gtest/gtest.h>

//#include "Tank.h"
//#include "Missile.h"

<<<<<<< HEAD:source-code/program/ClassTests.cpp
=======
//Needed to compile the tests in my project:
//#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Manager.h"
//#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\CollisionManager.h"
//
//#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Tank.h"
//#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Missile.h"
//#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Orientation.h"

/*NOTE: All exceptions are incomplete and commented out*/

>>>>>>> origin/master:source-code/google-tests/ClassTests.cpp
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

    EXPECT_TRUE(isCollision(rect_A, rect_B));
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

TEST(Orientation, moveFunctionCorrectlyChangesCoodinates)
{
    float originX = 10.0;
    float originY = 12.0;
    float rotation = 0.0;
    float height = 5;
    float width = 10;

    Orientation orientationTest(originX,originY,width,height,rotation);
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
