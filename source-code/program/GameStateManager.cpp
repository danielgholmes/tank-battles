//! Implementation for GameStateManager class.
/*! This manager is responsible for managing the timing of the game, which
    includes tha timer for the game run time. The other timers that it manages
    have to do with the timing between firing of missiles and laying of mines
    of each of the players' tanks.
    \file       CollisionManager.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/

#include "GameStateManager.h"

//! Constructor for GameStateManager.
/*! Initialises the timer for the whole game.
*/
GameStateManager::GameStateManager()
{
    _game_timer.start();
}

//! Main manage function.
/*! The amount of elapsed time is obtained by getting the timer value and subtracting that from
    the game runtime variable. Once that timer runs out, the game state will be set to finished.
    Otherwise the current game time is set. Attack timers are also run.
    \param game_data_container :: Information that holds the game time which will be changed accordingly
*/
void GameStateManager::manage(GameManagementData& game_data_container)
{
    if (!_game_timer.isRunning())
        _game_timer.start();

    double current_time = _game_runtime - _game_timer.getTimerValue();// makes the timer countdown

    if (current_time <= 0 )
    {
        _game_timer.stop();
        game_data_container.setGameFinished(); // finish the game
    }
    else
        game_data_container.setGameTime(current_time);

    manageAttackTimers(game_data_container);
}

//! Manage the timers that keep track of firing and laying mines intervals.
/*! Both players' timers are checked. If their time for firing has run out then thay may fire
    another missile, or lay another mine.
    \param game_data_container :: Information about whhat attacks the players' desire
*/
void GameStateManager::manageAttackTimers(ActionData& game_data_container)
{
    auto actions = game_data_container.giveActionInfo();

    if (actions.attack_1 == fire_missile)
    {
        if (!timeRunOut(_p1_fire_timer))
            game_data_container.resetP1Attack();
    }

    if (actions.attack_2 == fire_missile)
    {
        if (!timeRunOut(_p2_fire_timer))
            game_data_container.resetP2Attack();
    }


    if (actions.attack_1 == lay_mine)
    {
        if (!timeRunOut(_p1_lay_mine_timer))
            game_data_container.resetP1Attack();
    }

    if (actions.attack_2 == lay_mine)
    {
        if (!timeRunOut(_p2_lay_mine_timer))
            game_data_container.resetP2Attack();
    }
}

//! Checks timeout for specific timer
/*! If the timer is not running yet, then it is started. If it has started, the attack time
    is calculated.
    \param timer :: timer to be checked
    \return bool
*/
bool GameStateManager::timeRunOut(StopWatch& timer)
{
    if (!timer.isRunning())
    {
        timer.start();
        return true;
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
