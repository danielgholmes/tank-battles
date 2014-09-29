/**
 * \file StopWatch.cpp
 * \brief contains all implementation for StopWatch class
 */

#include "StopWatch.h"
#include <ctime>
#include <iostream>

StopWatch::StopWatch():
    _stop(0.0),
    _start(0.0),
    _running(false)
// initiliase private variables
{}

void StopWatch::start()
{
    _start = getProcessTime() - _stop;
    _running = true;
    //std::cout << "Stopwatch started..." << std::endl;
}

void StopWatch::stop()
{
    if (isRunning())
    {
        _stop = getProcessTime() - _start;
        _running = false;
        //std::cout << "Stopwatch stopped at: " << _stop << std::endl;
    }
}

void StopWatch::lap()
{
    //if (isRunning())
        //std::cout << "Lap: " << (getProcessTime() - _start) << std::endl;

}

void StopWatch::reset()
{
    if (isRunning())
    {
        _stop = 0.0;
        //std::cout << "Stopwatch reset..." << std::endl;
        start();
    }
}

// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing
double StopWatch::getProcessTime()
{
	clock_t time = clock();
	return static_cast<double>(time)/CLOCKS_PER_SEC;
}

bool StopWatch::isRunning()
{
    if (_running)
        return true;
    else
        //std::cout << "Stopwatch isn't running." << std::endl;
    return false;
}

double StopWatch::getTimerValue()
{
    if (isRunning())
        return getProcessTime() - _start;
}
