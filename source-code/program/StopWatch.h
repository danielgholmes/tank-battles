//! Responsible for keeping time
/*! This class was originally developed as part of the Software Development II course
    at Wits University. It has been modified considerably, particularly it's implementation.
    The class provides general time keeping functionality.
    \file       StopWatch.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
    \brief      Description of StopWatch class
*/

#ifndef STOPWATCH_H
#define STOPWATCH_H

/// Responsible for keeping time
class StopWatch {
public:
    StopWatch();
    void start();
    void stop();
    void lap();
    void reset();
    bool isRunning();
    double getTimerValue();

private:
    /// Holds the system time from when the stopwatch starts
    double _start;
    /// Holds the stopped or total clock running time
    double _stop;
    /// Used to tell if the stopwatch is running
    bool _running;
    double getProcessTime();
};



#endif
