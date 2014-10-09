//! Implementation for the GameManagementData Class
/*! GameManagementData serves as a dynamic data container which is passed around
    during the game management cycle. It holds basic getter and setter functions
    which are visible to only certain managers at specific times.
    \class      GameManagementData
    \file       GameManagementData.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
 */

 #include "GameManagementData.h"

//! Constructor for GameManagementData object.
/*! Initialises all private data members to a zero state. The reset actions info
    funcition called during the constructor ensures the struct held by the class is
    set to zero as well.
*/
 GameManagementData::GameManagementData():
     _p1_score(0),
     _p2_score(0),
     _game_time(0),
     _p1_respawn(false),
     _p2_respawn(false),
     _game_state(false)
     {
        resetActionsInfo();
     }

//! Reset The actions_info structure values to zero
/*! All values are reduced from their current state to a default
    idle state
*/
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

//! Getter for the actions_info object
/*! This retrieves the current version of the actions_info
    container
    \return actions_info
*/
const actions_info& GameManagementData::giveActionInfo() const
{
    return _game_actions;
}

//! Function to reset the firing state of turrets
/*! This function will prevent turrets from continually firing at
    a players tank
*/
void GameManagementData::resetTurretFire()
{
    _game_actions.turret_fire = false;
}

//! Function to set the firing state of turrets
/*! This funcion will cause turrets to fire at a players
    tank in its proximity
*/
void GameManagementData::setTurretFire()
{
    _game_actions.turret_fire = true;
}

//! Sets p1 to move forward
/*! This is a simple setter for p1 forward movement
*/
void GameManagementData::moveForwardP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = forward;
}

//! Sets p1 to move backward
/*! This is a simple setter for p1 backward movement
*/
void GameManagementData::moveBackwardP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = reverse;
}

//! Sets p1 to rotate left
/*! This is a simple setter for p1 left rotation
*/
void GameManagementData::rotateLeftP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = rotate_left;
}

//! Sets p1 to rotate right
/*! This is a simple setter for p1 right rotation
*/
void GameManagementData::rotateRightP1()
{
    _game_actions.change_1 = true;
    _game_actions.move_1 = rotate_right;
}

//! Sets p2 to move forward
/*! This is a simple setter for p2 forward movement
*/
void GameManagementData::moveForwardP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = forward;
}

//! Sets p2 to move backward
/*! This is a simple setter for p2 backward movement
*/
void GameManagementData::moveBackwardP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = reverse;
}

//! Sets p2 to rotateLeft
/*! This is a simple setter for p2 left rotation
*/
void GameManagementData::rotateLeftP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = rotate_left;
}

//! Sets p2 to rotate right
/*! This is a simple setter for p2 right rotation
*/
void GameManagementData::rotateRightP2()
{
    _game_actions.change_2 = true;
    _game_actions.move_2 = rotate_right;
}

//! Sets condition for p1 to fire missile
/*! This is a simple setter for p1 missile firing
*/
void GameManagementData::missileFiredP1()
{
    _game_actions.change_1 = true;
    _game_actions.attack_1 = fire_missile;
}

//! Sets condition for p2 to fire missile
/*! This is a simple setter for p2 missile firing
*/
void GameManagementData::missileFiredP2()
{
    _game_actions.change_2 = true;
    _game_actions.attack_2 = fire_missile;
}

//! Sets condition for p1 to lay a mine
/*! This is a simple setter for p1 to lay a mine
*/
void GameManagementData::mineLaidP1()
{
    _game_actions.change_1 = true;
    _game_actions.attack_1 = lay_mine;
}

//! Sets condition for p2 to lay a mine
/*! This is a simple setter for p2 to lay a mine
*/
void GameManagementData::mineLaidP2()
{
    _game_actions.change_2 = true;
    _game_actions.attack_2 = lay_mine;
}

//! This stops p1 from attacking
/*! P1 cannot fire for the current management cycle
*/
void GameManagementData::resetP1Attack()
{
    _game_actions.attack_1 = do_nothing;
}

//! This stops p2 from attacking
/*! P1 cannot fire for the current management cycle
*/
void GameManagementData::resetP2Attack()
{
    _game_actions.attack_2 =do_nothing;
}

//! Retrieve p1 score
/*! This is a simple getter method
*/
const int GameManagementData::getP1Score()
{
    return _p1_score;
}

//! Retrieve p2 score
/*! This is a simple getter method
*/
const int GameManagementData::getP2Score()
{
    return _p2_score;
}

//! Increment p1 score
/*! This increments p1's score by one point
*/
void GameManagementData::increaseP1Score()
{
    _p1_score++;
    _p1_respawn = true;
}


//! Increment p2 score
/*! This increments p2's score by one point
*/
void GameManagementData::increaseP2Score()
{
    _p2_score++;
    _p2_respawn = true;
}

//! Allow p1 to respwan again
/*! This function allows the Game object to create another tank player once
    it has been destroyed
*/
void GameManagementData::setP1Respawn()
{
    _p1_respawn = true;
}

//! Allow p2 to respwan again
/*! This function allows the Game object to create another tank player once
    it has been destroyed
*/
void GameManagementData::setP2Respawn()
{
    _p2_respawn = true;
}

//! Disallow p1 to respwan again
/*! This function stops the Game object from creating another tank player while it is
    alive it has been destroyed
*/
void GameManagementData::disableP1Respawn()
{
    _p1_respawn = false;
}

//! Disallow p2 to respwan again
/*! This function stops the Game object from creating another tank player while it is
    alive it has been destroyed
*/
void GameManagementData::disableP2Respawn()
{
    _p2_respawn = false;
}


//! Check boolean state of the respawn condition
/*! Check for changes to see if p1 needs to be respawned
*/
const bool GameManagementData::isP1Respawn()
{
    return _p1_respawn;
}

//! Check boolean state of the respawn condition
/*! Check for changes to see if p2 needs to be respawned
*/
const bool GameManagementData::isP2Respawn()
{
    return _p2_respawn;
}

//! Check boolean state of the game
/*! This function will return a true result after 2 minutes of the
    game running.
    \return bool
*/
const bool GameManagementData::isGameFinished()
{
    return _game_state;
}

//! Set the game to be finished
/*! This function is called after 2 minutes of gameplay
*/
void GameManagementData::setGameFinished()
{
    _game_state = true;
}

//! Update the current time of the game display clock
/*! This is used by draw and StateManager to render the game clock
    \param game_time :: the current game time retrueved from the GameStateManager
*/
void GameManagementData::setGameTime(const float game_time)
{
    _game_time = game_time;
}

//! Function to fetch the current game time
/*! Returns the value of the current game timer within GameStateManager
*/
const float GameManagementData::getGameTime()
{
    return _game_time;
}

GameManagementData::~GameManagementData()
{

}
