/**
 * \class   Keyboard
 * \file 	Keyboard.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	29 September 2014
 * \brief 	Class that interfaces between the game and SFML keyboard class
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "SFML/Graphics.hpp"

#include "Structures.h" // contains the gameplay_keys struct

class Keyboard
{
public:
    bool isKeyPressed(gameplay_keys key_input);
};
#endif // KEYBOARD_H_
