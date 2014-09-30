/**
 * \file 	NewGame.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Game class and the Game is instansiated within this file
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

//    display->displayGameEndScreen();

    std::cout << "Thank you for playing Tank-battle v1.1 !" << std::endl;
    std::cout << "see: " << std::endl << "https://github.com/danielgholmes/tank-battles" << std::endl << "for latest version :D " << std::endl;

}
