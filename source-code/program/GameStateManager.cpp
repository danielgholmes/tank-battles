/**
 * \file 	CollisionManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	22 September 2014
 * \brief 	Class that manages all collidable objects
 */

#include "GameStateManager.h"

GameStateManager::GameStateManager()
    //Constructor for timer goes here
{
    _game_timer.start();
}

void GameStateManager::manage(game_state_info& game_state)
{
    if (!_game_timer.isRunning())
        _game_timer.start();

    double current_time = _game_runtime - _game_timer.getTimerValue();// makes the timer countdown

    if (current_time <= 0 )
    {
        _game_timer.stop();
        game_state.finished = true; // finish the game
    }
    else
        game_state.runtime = current_time;


}

GameStateManager::~GameStateManager()
{

}
