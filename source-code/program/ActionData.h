/**
 * \class  ActionData
 * \file   ActionData.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   29 September 2014
 * \brief  Abstract-Base class responsible for defining the interface for
 *         handling all dynamic, user-related/generated data, within the game world
 */

#ifndef ACTIONDATA_H_
#define ACTIONDATA_H_

#include "Structures.h"

class ActionData
{
public:

    ///Virtual void function, look to child for defenition
    virtual void resetActionsInfo() = 0;
    ///
    virtual const actions_info& giveActionInfo() = 0;
    ///
    virtual void resetTurretFire() = 0;
    ///
    virtual void setTurretFire() = 0;
    ///
    virtual void moveForwardP1() = 0;
    ///
    virtual void moveBackwardP1() = 0;
    ///
    virtual void rotateLeftP1() = 0;
    ///
    virtual void rotateRightP1() = 0;
    ///
    virtual void moveForwardP2() = 0;
    ///
    virtual void moveBackwardP2() = 0;
    ///
    virtual void rotateLeftP2() = 0;
    ///
    virtual void rotateRightP2() = 0;
    ///
    virtual void missileFiredP1() = 0;
    ///
    virtual void missileFiredP2() = 0;
    ///
    virtual void mineLaidP1() = 0;
    ///
    virtual void mineLaidP2() = 0;
    ///
    virtual void resetP1Attack() = 0;
    ///
    virtual void resetP2Attack() = 0;
    ///
    virtual ~ActionData() {};

private:

};

#endif // ACTIONDATA_H_
