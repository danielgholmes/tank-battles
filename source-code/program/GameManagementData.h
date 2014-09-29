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
    void resetActionsInfo();
    ///
    void resetTurretFire();
    ///
    void setTurretFire();
    ///
    void missileFiredP1();
     ///
    void missileFiredP2();
    ///
    void mineLaidP1();
    ///
    void mineLaidP2();
    ///
    const player_action& getAttackTypeP1();
    ///
    const player_action& getAttackTypeP2();
     ///
    void increaseP1Score();
    ///
    void increaseP2Score();
    ///
    void setP1Respawn();
    ///
    void setP2Respawn();
    ///
    void disableP1Respawn();
    ///
    void disableP2Respawn();
    ///
    const bool isP1Respawn();
    ///
    const bool isP2Respawn();
    ///
    const bool isGameFinished();
    ///Destructor
    virtual ~GameManagementData();

private:

    actions_info _game_actions;
    int _p1_score;
    int _p2_score;
    bool _p1_respawn;
    bool _p2_respawn;
    bool _game_state;

};

#endif // GAMEMANAGEMENTDATA_H_
