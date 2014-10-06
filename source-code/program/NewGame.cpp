/**
 * \file 	NewGame.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Game class and the Game is instansiated within this file
 */

 /**
\mainpage Tanks A Lot Game Software Documentation

Place cute message here
*/

//includes
#include "Game.h"
#include "Display.h"
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<Display> display(new Display(1200,675));

    Game TankWorld;
    TankWorld.runWorld(display);

    std::cout << "Tanks A Lot for Playing!" << std::endl;
    std::cout << "see: " << std::endl << "https://github.com/danielgholmes/tank-battles" << std::endl << "for latest version :D " << std::endl;

}
