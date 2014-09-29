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
     _game_state(true)
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

void GameManagementData::resetTurretFire()
{
    _game_actions.turret_fire = false;
}

void GameManagementData::setTurretFire()
{
    _game_actions.turret_fire = true;
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

const player_action& GameManagementData::getAttackTypeP1()
{
    return _game_actions.attack_1;
}

const player_action& GameManagementData::getAttackTypeP2()
{
    return _game_actions.attack_2;
}

void GameManagementData::increaseP1Score()
{
    _p1_score++;
}

void GameManagementData::increaseP2Score()
{
    _p2_score++;
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

GameManagementData::~GameManagementData()
{

}
