/**
 * \class  GameManagementData
 * \file   GameManagementData.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   29 September 2014
 * \brief  Compositional class responsible for defining the interface for
 *         handling all game-runtime variables and player related actions.
 */

#ifndef GAMEMANAGEMENTDATA_H_
#define GAMEMENAGEMENTDATA_H_

#include "ActionData.h"
#include "GameStateData.h"

class GameManagementData: public ActionData, public GameStateData
{
public:

    ///Constructor
    GameManagementData();
    ///Virtual void function, look to child for defenition
    virtual void resetActionsInfo();
    ///
    virtual const actions_info& giveActionInfo();
    ///
    virtual void resetTurretFire();
    ///
    virtual void setTurretFire();
    ///
    virtual void moveForwardP1();
    ///
    virtual void moveBackwardP1();
    ///
    virtual void rotateLeftP1();
    ///
    virtual void rotateRightP1();
    ///
    virtual void moveForwardP2();
    ///
    virtual void moveBackwardP2();
    ///
    virtual void rotateLeftP2();
    ///
    virtual void rotateRightP2();
    ///
    virtual void missileFiredP1();
     ///
    virtual void missileFiredP2();
    ///
    virtual void mineLaidP1();
    ///
    virtual void mineLaidP2();
    ///
    virtual void resetP1Attack();
    ///
    virtual void resetP2Attack();


    ///
    virtual const int geP1Score();
    ///
    virtual const int getP2Score();
    ///
    virtual void increaseP1Score();
    ///
    virtual void increaseP2Score();
    ///
    virtual void setP1Respawn();
    ///
    virtual void setP2Respawn();
    ///
    virtual void disableP1Respawn();
    ///
    virtual void disableP2Respawn();
    ///
    virtual const bool isP1Respawn();
    ///
    virtual const bool isP2Respawn();
    ///
    virtual const bool isGameFinished();
    ///
    virtual void setGameFinished();
    ///
    virtual virtual void setGameTime(const float game_time);
    ///
    virtual virtual const float getGameTime();
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
