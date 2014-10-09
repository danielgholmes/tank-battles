//! An Abstract-based class providing an interface for action data containing classes
/*! This class is used as a interface-parent for a classes which will hold action data
    for the game. It defines an array of pure virtual getters and setters which can
    be implemented in various ways for versitiliy.
    \file       ActionData.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
 */

#ifndef ACTIONDATA_H_
#define ACTIONDATA_H_

#include "Structures.h"

class ActionData
{
public:

    /// Virtual void function, look to child for defenition
    virtual void resetActionsInfo() = 0;
    /// Provide the actions_info structure of a class
    virtual const actions_info& giveActionInfo() const = 0;
    /// Virtual void function, look to child for defenition
    virtual void resetTurretFire() = 0;
    /// Virtual void function, look to child for defenition
    virtual void setTurretFire() = 0;
    /// Virtual void function, look to child for defenition
    virtual void moveForwardP1() = 0;
    /// Virtual void function, look to child for defenition
    virtual void moveBackwardP1() = 0;
    /// Virtual void function, look to child for defenition
    virtual void rotateLeftP1() = 0;
    /// Virtual void function, look to child for defenition
    virtual void rotateRightP1() = 0;
    /// Virtual void function, look to child for defenition
    virtual void moveForwardP2() = 0;
    /// Virtual void function, look to child for defenition
    virtual void moveBackwardP2() = 0;
    /// Virtual void function, look to child for defenition
    virtual void rotateLeftP2() = 0;
    /// Virtual void function, look to child for defenition
    virtual void rotateRightP2() = 0;
    /// Virtual void function, look to child for defenition
    virtual void missileFiredP1() = 0;
    /// Virtual void function, look to child for defenition
    virtual void missileFiredP2() = 0;
    /// Virtual void function, look to child for defenition
    virtual void mineLaidP1() = 0;
    /// Virtual void function, look to child for defenition
    virtual void mineLaidP2() = 0;
    /// Virtual void function, look to child for defenition
    virtual void resetP1Attack() = 0;
    /// Virtual void function, look to child for defenition
    virtual void resetP2Attack() = 0;
    /// Destructor for Action Data
    virtual ~ActionData() {};

private:

};

#endif // ACTIONDATA_H_
