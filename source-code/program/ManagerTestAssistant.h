/**
 * \class  ManagerTestAssistant
 * \file   ManagerTestAssistant.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   03 October 2014
 * \brief  Class to assist in the correct running of Google Tests
 */

#ifndef MANAGERTESTASSISTANT_H_
#define MANAGERTESTASSISTANT_H_

//Includes
#include "Tank.h"
#include "Deletable.h"
#include "Collidable.h"
#include "Structures.h"
#include <memory>

class ManagerTestAssistant
{
public:

    std::shared_ptr<Deletable> createDeletableEntitySharedPointer(const entity_type entity);
};


#endif // MANAGERTESTASSISTANT_H_
