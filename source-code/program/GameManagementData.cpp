/**
 * \class  GameManagementData
 * \file   GameManagementData.cpp
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   29 September 2014
 * \brief  Compositional class responsible for defining the interface for
 *         handling all game-runtime variables and player related actions.
 */

 #include "GameManagementData.h"

 GameManagementData::GameManagementData():
     _p1_score(0),
     _p2_score(0),
     _p1_respawn(false),
     _p2_respawn(false),
     _game_state(true),
     _game_time(0)
     {
        resetActionsInfo();
     }

void GameManagementData::resetActionsInfo()
{
    _game_actions.change_1 = false;
	_game_actions.change_2 = false;
	_game_actions.turret_fire = false;
	_game_actions.move_1 = do_nothing;
	_game_actions.move_2 = do_nothing;
	_game_actions.attack_1 = do_nothing;
	_game_actions.attack_2 = do_nothing;
}

const actions_info& GameManagementData::giveActionInfo()
{
    return _game_actions;
}

void GameManagementData::resetTurretFire()
{
    _game_actions.turret_fire = false;
}

void GameManagementData::setTurretFire()
{
    _game_actions.turret_fire = true;
}

void GameManagementData::moveForwardP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = forward;
}

void GameManagementData::moveBackwardP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = reverse;
}

void GameManagementData::rotateLeftP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = rotate_left;
}

void GameManagementData::rotateRightP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = rotate_right;
}

void GameManagementData::moveForwardP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = forward;
}

void GameManagementData::moveBackwardP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = reverse;
}

void GameManagementData::rotateLeftP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = rotate_left;
}

void GameManagementData::rotateRightP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = rotate_right;
}

void GameManagementData::missileFiredP1()
{
    _game_actions.change_1 = true;
    _game_actions.attack_1 = fire_missile;
}

void GameManagementData::missileFiredP2()
{
    _game_actions.change_2 = true;
    _game_actions.attack_2 = fire_missile;
}

void GameManagementData::mineLaidP1()
{
    _game_actions.change_1 = true;
    _game_actions.attack_1 = lay_mine;
}

void GameManagementData::mineLaidP2()
{
    _game_actions.change_2 = true;
    _game_actions.attack_2 = lay_mine;
}

void GameManagementData::resetP1Attack()
{
    _game_actions.attack_1 = do_nothing;
}

void GameManagementData::resetP2Attack()
{
    _game_actions.attack_2 =do_nothing;
}

const int GameManagementData::getP1Score()
{
    return _p1_score;
}

const int GameManagementData::getP2Score()
{
    return _p2_score;
}

void GameManagementData::increaseP1Score()
{
    _p1_score++;
    _p1_respawn = true;
}

void GameManagementData::increaseP2Score()
{
    _p2_score++;
    _p2_respawn = true;
}

void GameManagementData::setP1Respawn()
{
    _p1_respawn = true;
}

void GameManagementData::setP2Respawn()
{
    _p2_respawn = true;
}

void GameManagementData::disableP1Respawn()
{
    _p1_respawn = false;
}

void GameManagementData::disableP2Respawn()
{
    _p2_respawn = false;
}

const bool GameManagementData::isP1Respawn()
{
    return _p1_respawn;
}

const bool GameManagementData::isP2Respawn()
{
    return _p2_respawn;
}

const bool GameManagementData::isGameFinished()
{
    return _game_state;
}

void GameManagementData::setGameFinished()
{
    _game_state = false;
}

void setGameTime(const float game_time)
{
    _game_time = game_time;
}

const float getGameTime()
{
    return _game_time;
}

GameManagementData::~GameManagementData()
{

}
