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



