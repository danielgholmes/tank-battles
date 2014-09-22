/**
 * \file 	NewGame.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Game class and the Game is instansiated within this file
 */

//includes
#include "Game.h"
#include <iostream>

using namespace std;

int main()
{
    Game StartNewGame(1200,675);

    StartNewGame.runWorld();
    cout << "Thank you for playing Tank-battle v1.0 !" << endl;
    cout << "see: " << endl << "https://github.com/danielgholmes/tank-battles" << endl << "for latest version :D " << endl;

}
