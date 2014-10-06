//! Simple class to act as an interface for SFML keyboard functions
/*! This class has SFML keyboard input. It is design is such a way as to allow the 
	decoupling of SFML from
    \file       Keyboard.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "SFML/Graphics.hpp"

#include "Structures.h" // contains the gameplay_keys struct

/// Simple class to act as an interface for SFML keyboard functions.
class Keyboard
{
public:
    bool isKeyPressed(gameplay_keys key_input);
};
#endif // KEYBOARD_H_
