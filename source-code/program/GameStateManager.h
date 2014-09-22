/**
 * \class 	GameStateManager
 * \file 	GameStateManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	22 September 2014
 * \brief 	Class that manages all collidable objects
 */

#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_

class GameStateManager
{
public:

    ///Constructor
    GameStateManager();
    ///Function to manage the current game state
    void manage(bool& game_state);
    ///Destructor
    ~GameStateManager();

private:

    int _p1_score;
    int _p2_score;
    //Will add other members such as the timer class

};

#endif // _GAMESTATEMANAGER_H_

