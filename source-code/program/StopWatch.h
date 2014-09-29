/**
 * \class StopWatch.h
 * \author Daniel Holmes
 * \date 30 July 2014
 * \brief contains the interface for StopWatch class
 *
 */

#ifndef STOPWATCH_H
#define STOPWATCH_H

class StopWatch {
public:

    /// constructor that creates a StopWatch object
    StopWatch();

    /// starts the stopwatch
    void start();

    /// returns stop the time of the StopWatch
    void stop();

    /// returns the lap time
    void lap();

    /// reset the stopwatch
    void reset();

    /// checks if the stopwatch is running
    bool isRunning();

    /// gets the current value of the stopwatch
    double getTimerValue();

private:
    /// variable that holds the system time from when the stopwatch starts
    double _start;

    /// variable that holds the stopped or total clock running time
    double _stop;

    /// variable that is used to tell if the stopwatch is running
    bool _running;

    /// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing
    double getProcessTime();
};



#endif
