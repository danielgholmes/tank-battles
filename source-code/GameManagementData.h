//! A data containter class which is passed to all managers.
/*! GameManagementData serves as a dynamic data container which is passed around
    during the game management cycle. It holds basic getter and setter functions
    which are visible to only certain managers at specific times.
    \file       GameManagementData.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
 */

#ifndef GAMEMANAGEMENTDATA_H_
#define GAMEMANAGEMENTDATA_H_

#include "ActionData.h"
#include "GameStateData.h"

class GameManagementData: public ActionData, public GameStateData
{
public:

    /// Constructor
    GameManagementData();
    /// Virtual void function, look to child for defenition
    virtual void resetActionsInfo();
    /// Returns the action data container held by the class
    virtual const actions_info& giveActionInfo() const;
    /// Reset the firing condition of the game Turrets
    virtual void resetTurretFire();
    /// Enable the firing conditon of the game Turrets
    virtual void setTurretFire();
    /// Set Player1 to move forward
    virtual void moveForwardP1();
    /// Set player2 to move forward
    virtual void moveBackwardP1();
    /// Set player1 to rotate left
    virtual void rotateLeftP1();
    /// Set player1 to rotate right
    virtual void rotateRightP1();
    /// Set player2 to move forward
    virtual void moveForwardP2();
    /// Set player 2 to move backward
    virtual void moveBackwardP2();
    /// Set player 2 to rotate left
    virtual void rotateLeftP2();
    /// Set player 2 to rotate right
    virtual void rotateRightP2();
    /// Set missile for player 1 fired
    virtual void missileFiredP1();
     /// Set missile for player 2 fired
    virtual void missileFiredP2();
    /// Set mine laid for player 1
    virtual void mineLaidP1();
    /// Set mine laid for player 2
    virtual void mineLaidP2();
    /// Restt player1 attack state
    virtual void resetP1Attack();
    /// Reset player2 attack state
    virtual void resetP2Attack();

    /// Getter for p1 score
    virtual const int getP1Score();
    /// Getter for p2 score
    virtual const int getP2Score();
    /// Increment p1 score by 1
    virtual void increaseP1Score();
    /// Increment p2 score by 1
    virtual void increaseP2Score();
    /// Set p1 to respawn
    virtual void setP1Respawn();
    /// Set p2 to respawn
    virtual void setP2Respawn();
    /// Disable p1 to respawn
    virtual void disableP1Respawn();
    /// Disable p2 to respawn
    virtual void disableP2Respawn();
    /// Check if p1 is respawnable
    virtual const bool isP1Respawn();
    /// Check if p2 is respawnable
    virtual const bool isP2Respawn();
    /// Check if Game is in a finished  state
    virtual const bool isGameFinished();
    /// Set game in a finishe state
    virtual void setGameFinished();
    /// Set the game time
    virtual void setGameTime(const float game_time);
    /// Retrieve the game time for draw manager
    virtual const float getGameTime();
    ///Destructor
    virtual ~GameManagementData();

private:

    actions_info _game_actions;
    int _p1_score;
    int _p2_score;
    bool _p1_respawn;
    bool _p2_respawn;
    bool _game_state;
    float _game_time;

};

#endif // GAMEMANAGEMENTDATA_H_
