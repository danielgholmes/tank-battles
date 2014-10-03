/**
 * \class  ManagerTestAssistant
 * \file   ManagerTestAssistant.cpp
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   03 October 2014
 * \brief  Class to assist in the correct running of Google Tests
 */

#include "ManagerTestAssistant.h"

std::shared_ptr<Deletable> ManagerTestAssistant::createDeletableEntitySharedPointer(const entity_type entity)
{
    switch(entity)
    {
        p1_tank:
            {
                std::shared_ptr<Deletable> newTank(new Tank(10,10,0,p1_tank));
                return (newTank);
            }
        break;
    }
}
