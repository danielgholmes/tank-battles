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

void GameStateManager::manage(game_state_info& game_state, actions_info& actions)
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

    manageAttackTimers(actions);
}

void GameStateManager::manageAttackTimers(actions_info& actions)
{
    if (actions.attack_1 == fire_missile && !timeRunOut(_p1_fire_timer, actions))
        actions.attack_1 = do_nothing;

    if (actions.attack_2 == fire_missile && !timeRunOut(_p2_fire_timer, actions))
        actions.attack_2 = do_nothing;

    if (actions.attack_1 == lay_mine && !timeRunOut(_p1_lay_mine_timer, actions))
        actions.attack_1 = do_nothing;

    if (actions.attack_2 == lay_mine && !timeRunOut(_p2_lay_mine_timer, actions))
        actions.attack_2 = do_nothing;
}

bool GameStateManager::timeRunOut(StopWatch& timer, actions_info& actions)
{
    if (!timer.isRunning())
    {
        timer.start();
        return false;
    }

    double timer_time = _attack_time_limit - timer.getTimerValue();
    if (timer_time <= 0)
    {
        timer.reset();
        return true;
    }
    else return false;

}

GameStateManager::~GameStateManager()
{

}
