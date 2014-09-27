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

    //Remove any "corpses" found within the movable vector
    removeGarbage();


    auto moveables_iterator = _movables.begin();
    for(; moveables_iterator != _movables.end(); moveables_iterator++)
    {
        //Convert iterator to Weak pointer
        std::weak_ptr<Movable> entity_mov_wp = (*moveables_iterator);

        //Lock as Shared Pointer
        std::shared_ptr<Movable> entity_mov_sp = entity_mov_wp.lock();

        //Make changes to player 1's tank if movement has been captured
        if ((managerInstructions.change_1 == true) && (entity_mov_sp->getType() == p1_tank))
        {
            if(!entity_mov_sp->isBlocked())
            {
                switch(managerInstructions.move_1)
                {
                    case forward:
                        entity_mov_sp->moveForward();
                        entity_mov_sp->setMovementDirection(moveForward);
                        break;

                    case reverse:
                        entity_mov_sp->moveBackward();
                        entity_mov_sp->setMovementDirection(moveBackward);
                        break;

                    case rotate_left:
                        entity_mov_sp->rotateLeft();
                        entity_mov_sp->setMovementDirection(rotateLeft);
                        break;

                    case rotate_right:
                        entity_mov_sp->rotateRight();
                        entity_mov_sp->setMovementDirection(rotateRight);
                        break;

                    case do_nothing:
                        break;
                }
            }
            else //if the object is blocked
            {
                switch(managerInstructions.move_1)
                {
                    case forward:
                        entity_mov_sp->setMovementDirection(moveForward);
                    break;

                    case reverse:
                        entity_mov_sp->setMovementDirection(moveBackward);
                        break;

                    case rotate_left:
                        entity_mov_sp->setMovementDirection(rotateLeft);
                        break;

                    case rotate_right:
                        entity_mov_sp->setMovementDirection(rotateRight);
                    case do_nothing:
                        break;
                }
            }
        }

         //Make changes to player 2's tank if movement has been captured
        if ((managerInstructions.change_2 == true) && (entity_mov_sp->getType() == p2_tank))
        {
            if(!entity_mov_sp->isBlocked())
            {
                switch(managerInstructions.move_2)
                {
                  case forward:
                        entity_mov_sp->moveForward();
                        entity_mov_sp->setMovementDirection(moveForward);
                        break;

                    case reverse:
                        entity_mov_sp->moveBackward();
                        entity_mov_sp->setMovementDirection(moveBackward);
                        break;

                    case rotate_left:
                        entity_mov_sp->rotateLeft();
                        entity_mov_sp->setMovementDirection(rotateLeft);
                        break;

                    case rotate_right:
                        entity_mov_sp->rotateRight();
                        entity_mov_sp->setMovementDirection(rotateRight);
                        break;

                    case do_nothing:
                        break;
                }
            }
            else //if the object is blocked
            {
                switch(managerInstructions.move_2)
                {
                   case forward:
                        entity_mov_sp->setMovementDirection(moveForward);
                    break;

                    case reverse:
                        entity_mov_sp->setMovementDirection(moveBackward);
                        break;

                    case rotate_left:
                        entity_mov_sp->setMovementDirection(rotateLeft);
                        break;

                    case rotate_right:
                        entity_mov_sp->setMovementDirection(rotateRight);
                    case do_nothing:
                        break;
                }
            }
        }

        //Missiles will always move along their trajectory each management cycle
        //Exception if a missile hits a barrier

        //Missile has hit a barrier
        if ((entity_mov_sp->getType() == p1_missile) && (entity_mov_sp->isBlocked()))
        {
            entity_mov_sp->rotateLeft();
            entity_mov_sp->rotateLeft();
            entity_mov_sp->moveForward();
        }
        //Missile moves forward
        else if (entity_mov_sp->getType() == p1_missile)
        {
            entity_mov_sp->moveForward();
        }

        //P2 Missile has hit a barrier
        if ((entity_mov_sp->getType() == p2_missile) && (entity_mov_sp->isBlocked()))
        {
            entity_mov_sp->rotateLeft();
            entity_mov_sp->rotateLeft();
            entity_mov_sp->moveForward();
        }
        //P2 Missile moves forward
        else if (entity_mov_sp->getType() == p2_missile)
        {
            entity_mov_sp->moveForward();
        }

    }//Range-based for
}//Function

void MoveManager::removeGarbage()
{
    auto removable = _movables.begin();
    for (; removable != _movables.end();)
    {
        //Convert iterator to Weak pointer
        std::weak_ptr<Movable> removable_wp = (*removable);
        //Lock as Shared Pointer
        std::shared_ptr<Movable> removable_sp = removable_wp.lock();
        //Test to see if the shared pointer exists
        if (removable_sp)
        {
            removable++;
        }
        else
        {
            _movables.erase(removable);
        }
    }
}

void MoveManager::addNewEntity(std::weak_ptr<Movable> new_entity)
{
    _movables.push_back(new_entity);
}
