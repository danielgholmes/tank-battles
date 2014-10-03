//File used for testing speed performance of Battle Tanks Game
//Authors: Jonathan Gerrand 349361 and Daniel Holmes 551240

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <map>
#include "math.h"
#include <memory>
#include <iostream>
#include <fstream>

//Structures and enums
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Structures.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\SpriteDimensions.h"

//include all entites
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Tank.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Missile.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Barrier.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Mine.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Turret.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\GameManagementData.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\GameStateData.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\ActionData.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Display.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\Keyboard.h"

//include all managers
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\MoveManager.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\CollisionManager.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\TrackingManager.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\DrawManager.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\DestructionManager.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\GameStateManager.h"
#include "C:\Users\Priscilla Gerrand\Desktop\Wits 2014\ELEN3009 - Software\Project\Workspace\tank-battles\source-code\program\TurretManager.h"

///================================= Code written by blueJamesBond, http://stackoverflow.com/questions/876901/calculating-execution-time-in-c ===============
#include <time.h>
clock_t startm, stopm;
#define START if ( (startm = clock()) == -1) {printf("Error calling clock");exit(1);}
#define STOP if ( (stopm = clock()) == -1) {printf("Error calling clock");exit(1);}
#define PRINTTIME printf( "%6.3f seconds used by the processor.", ((double)stopm-startm)/CLOCKS_PER_SEC);
///===========================================================================================================================================================

using namespace std;

int main()
{
    GameManagementData data;
    std::shared_ptr<Display> display(new Display(1250,850));

    MoveManager moveManager;
    CollisionManager collisionManager;
    DestructionManager destructionManager;
    TrackingManager trackingManager;
    DrawManager drawManager;

    ofstream myfile;
    myfile.open ("BattleTanksTiming.txt");

    for(int j = 1; j < 30; j ++)
    {
        int i = 0;
        for(; i < 10*j; i++)
        {
            std::shared_ptr<Deletable> missile_del_sp(new Missile(10, 10, 0, p1_missile));
            std::weak_ptr<Collidable> missile_col_wp = std::dynamic_pointer_cast<Collidable>(missile_del_sp);
            std::weak_ptr<Movable> missile_mov_wp = std::dynamic_pointer_cast<Movable>(missile_del_sp);

            moveManager.addNewEntity(missile_mov_wp);
            destructionManager.addNewEntity(missile_del_sp);
            collisionManager.addNewEntity(missile_col_wp);
            drawManager.addNewEntity(missile_del_sp);
        }


        //Timing executions
        cout << endl << endl;
        cout << "Iteration No.: " << j <<endl;
        cout << "Num of Entities: " << i*j <<endl;

        myfile << "Iteration: " << j << ", " << "Num of entities: " << i*j << ", ";
        START;

        moveManager.manage(data);
        drawManager.manage(data,display);
        collisionManager.manage();
        destructionManager.manage(data);


        STOP;
        cout << "Time: " << ((double)stopm-startm)/CLOCKS_PER_SEC;
        myfile << "Time: " << ((double)stopm-startm)/CLOCKS_PER_SEC << endl;


    }
    myfile.close();
    return 0;
}
