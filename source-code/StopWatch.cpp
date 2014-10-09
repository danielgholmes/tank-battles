//! Implementation for time class
/*! This class was originally developed as part of the Software Development II course
    at Wits University. It has been modified considerably, particularly it's implementation.
    The class provides general time keeping functionality.
    \file       StopWatch.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/
#include "StopWatch.h"
#include <ctime>
#include <iostream>

//! Constuctor that initialises private class variables.
/*! 
*/
StopWatch::StopWatch():
    _stop(0.0),
    _start(0.0),
    _running(false)
{}

//! Starts the stopwatch.
/*! Set the running status to true.
*/
void StopWatch::start()
{
    _start = getProcessTime() - _stop;
    _running = true;
}

//! Stops the stopwatch.
/*! Set the running status to false and gets the stop time.
*/
void StopWatch::stop()
{
    if (isRunning())
    {
        _stop = getProcessTime() - _start;
        _running = false;
    }
}

//! Gives the lap time.
/*! 
*/
void StopWatch::lap()
{
    if (isRunning())
        std::cout << "Lap: " << (getProcessTime() - _start) << std::endl;

}

//! Resets the stopwatch.
/*! 
*/
void StopWatch::reset()
{
    if (isRunning())
    {
        _stop = 0.0;
        start();
    }
}

//! Returns the amount of time in seconds 
/*! The return time is the tim ethat has passed since the process 
    (i.e. the program) started executing
    \return double
*/
double StopWatch::getProcessTime()
{
	clock_t time = clock();
	return static_cast<double>(time)/CLOCKS_PER_SEC;
}

//! Check if the stopwatch is running
/*! \return bool
*/
bool StopWatch::isRunning()
{
    if (_running)
        return true;
    return false;
}

//! Gets the time since the stopwatch started
/*! \return double
*/
double StopWatch::getTimerValue()
{
    if (isRunning())
        return getProcessTime() - _start;
}
