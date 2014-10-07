//! Manager class responsible for managing state of the game
/*! This manager is responsible for managing the timing of the game, which
    includes tha timer for the game run time. The other timers that it manages
    have to do with the timing between firing of missiles and laying of mines
    of each of the players' tanks.
    \file       CollisionManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/

#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_

#include "GameManagementData.h"
#include "ActionData.h"
#include "StopWatch.h" //reused class from lab 2
#include "Structures.h"
#include "Manager.h"
#include <vector>

/// Manager class responsible for managing state of the game.
class GameStateManager: public Manager
{
public:
    GameStateManager();
    void manage(GameManagementData& game_data_container);
    ~GameStateManager();

private:
    /// Keeps track of the overall game time
    StopWatch _game_timer;
    /// Keep tracks of time between firing of missiles for player 1
    StopWatch _p1_fire_timer;
    /// Keep tracks of time between firing of missiles for player 2
    StopWatch _p2_fire_timer;
    /// Keeps track of time between laying mines for player 1
    StopWatch _p1_lay_mine_timer;
    /// Keeps track of time between laying mines for player 2
    StopWatch _p2_lay_mine_timer;
    /// The time in seconds of how long the game will last
    const double _game_runtime = 120.0;
    /// Time limit between firing or laying mines for tanks
    const double _attack_time_limit = 0.5;

    void manageAttackTimers(ActionData& action_data_container);
    bool timeRunOut(StopWatch& timer);
};

#endif // _GAMESTATEMANAGER_H_

