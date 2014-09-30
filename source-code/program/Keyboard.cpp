/**
 * \file 	Keyboard.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	29 September 2014
 * \brief 	Implementation keyboard class
 */

#include "Keyboard.h"

bool Keyboard::isKeyPressed(gameplay_keys key_input)
{
    switch(key_input)
    {
    case Left:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            return true;
        break;
    case Right:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            return true;
        break;
    case Up:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            return true;
        break;
    case Down:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            return true;
        break;
    case RAlt:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
            return true;
        break;
    case RControl:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            return true;
        break;
    case A:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            return true;
        break;
    case D:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return true;
        break;
    case W:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            return true;
        break;
    case S:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return true;
        break;
    case LAlt:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
            return true;
        break;
    case LControl:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            return true;
        break;
    }
    return false; // if the key is not pressed
}
