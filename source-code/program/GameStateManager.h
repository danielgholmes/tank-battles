/**
 * \class 	GameStateManager
 * \file 	GameStateManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	22 September 2014
 * \brief 	Class that manages all collidable objects
 */

#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_

#include "GameManagementData.h"
#include "ActionData.h"
#include "StopWatch.h" //reused class from lab 2
#include "Structures.h"
#include <vector>

class GameStateManager
{
public:

    ///Constructor
    GameStateManager();
    ///Function to manage the current game state
    void manage(GameManagementData& game_data_container);
    ///Destructor
    ~GameStateManager();

private:
    /// Object that keeps track of the game time
    StopWatch _game_timer;
    /// Objects that keep track of time between firing of missiles
    StopWatch _p1_fire_timer;
    StopWatch _p2_fire_timer;
    /// Objects that keep track of time between laying mines
    StopWatch _p1_lay_mine_timer;
    StopWatch _p2_lay_mine_timer;
    /// How long the game lasts
    const double _game_runtime = 120.0;
    /// Time limit between firing or laying mines for tanks
    const double _attack_time_limit = 0.5;

    void manageAttackTimers(ActionData& action_data_container);

    bool timeRunOut(StopWatch& timer);

};

#endif // _GAMESTATEMANAGER_H_

