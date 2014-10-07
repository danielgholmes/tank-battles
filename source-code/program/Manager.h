//! Abstract-Base Class of Managers
/*!
    \class 	    Manager
    \file 	    Manager.h
    \author 	Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date 	    2 September 2014

 */


#ifndef MANAGER_H_
#define MANAGER_H_

//Forward declarations

//Includes
#include <memory>


class Manager
{
public:
    ///Constructor for Manager
    Manager();

    ///Destructor
	virtual ~Manager();

};

#endif //Manager_H_
