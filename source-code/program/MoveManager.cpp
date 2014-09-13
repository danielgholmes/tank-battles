/**
 * /file 	MoveManager.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for MoveManager class
 */

#include "MoveManager.h"

MoveManager::MoveManager()
{

}

MoveManager::~MoveManager()
{

}

void MoveManager::manage(const actions_info& managerInstructions)
{
    for(auto entity: _movables)
    {
        std::weak_ptr<Movable> entity_wp = entity;
        // Convert weak_ptr to shared_ptr
        std::shared_ptr<Movable> entity_sp = entity_wp.lock();

        //Make changes to player 1's tank if movement has been captured
        if ((managerInstructions.change_1 == 1) && (entity_sp->getType() == p1_tank))
        {
            if(!entity_sp->isBlocked())
            {
                switch(managerInstructions.move_1)
                {

                    case forward:
                        entity_sp->moveForward();
                        break;

                    case reverse:
                        entity_sp->moveBackward();
                        break;

                    case rotate_left:
                        entity_sp->rotateLeft();
                        break;

                    case rotate_right:
                        entity_sp->rotateRight();
                        break;

                    case do_nothing:
                        break;
                }
            }
        }

         //Make changes to player 2's tank if movement has been captured
        if ((managerInstructions.change_2 == 1) && (entity_sp->getType() == p2_tank))
        {
            if(!entity_sp->isBlocked())
            {
                switch(managerInstructions.move_2)
                {

                    case forward:
                        entity_sp->moveForward();
                        break;

                    case reverse:
                        entity_sp->moveBackward();
                        break;

                    case rotate_left:
                        entity_sp->rotateLeft();
                        break;

                    case rotate_right:
                        entity_sp->rotateRight();
                        break;

                    case do_nothing:
                        break;
                }
            }
        }

        //Missiles will always move along their trajectory each management cycle
        //Exception if a missile hits a barrier

        //P1 Missile has hit a barrier
        if ((entity_sp->getType() == p1_missile) && (entity_sp->isBlocked()))
        {
            entity_sp->rotateLeft();
            entity_sp->moveForward();
        }
        //P1 Missile moves forward
        else if (entity_sp->getType() == p1_missile)
           entity_sp->moveForward();

        //P2 Missile has hit a barrier
        if ((entity_sp->getType() == p1_missile) && (entity_sp->isBlocked()))
        {
            entity_sp->rotateLeft();
            entity_sp->moveForward();
        }
        //P2 Missile moves forward
        else if (entity_sp->getType() == p1_missile)
           entity_sp->moveForward();


    }//Range-based for
}//Function

void MoveManager::addNewEntity(std::weak_ptr<Movable> new_entity)
{
    _movables.push_back(new_entity);
}

