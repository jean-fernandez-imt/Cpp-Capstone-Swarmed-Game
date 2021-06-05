#include <SDL2/SDL.h>

#include "timer.h"

Timer::Timer() {
    //Initialize the variables
    _startTicks = 0;
    _pausedTicks = 0;

    _paused = false;
    _started = false;
}

void Timer::start() {
    //Start the timer
    _started = true;

    //Unpause the timer
    _paused = false;

    //Get the current clock time
    _startTicks = SDL_GetTicks();
	_pausedTicks = 0;
}

void Timer::stop() {
    //Stop the timer
    _started = false;

    //Unpause the timer
    _paused = false;

	//Clear tick variables
	_startTicks = 0;
	_pausedTicks = 0;
}

void Timer::pause() {
    //If the timer is running and isn't already paused
    if(_started && !_paused) {
        //Pause the timer
        _paused = true;

        //Calculate the paused ticks
        _pausedTicks = SDL_GetTicks() - _startTicks;
		_startTicks = 0;
    }
}

void Timer::unpause() {
    //If the timer is running and paused
    if(_started && _paused) {
        //Unpause the timer
        _paused = false;

        //Reset the starting ticks
        _startTicks = SDL_GetTicks() - _pausedTicks;

        //Reset the paused ticks
        _pausedTicks = 0;
    }
}

std::size_t Timer::getTicks() {
	//The actual timer time
	std::size_t time = 0;

    //If the timer is running
    if(_started) {
        //If the timer is paused
        if(_paused) {
            //Return the number of ticks when the timer was paused
            time = _pausedTicks;
        } else {
            //Return the current time minus the start time
            time = SDL_GetTicks() - _startTicks;
        }
    }

    return time;
}

bool Timer::isStarted() {
	//Timer is running and paused or unpaused
    return _started;
}

bool Timer::isPaused()
{
	//Timer is running and paused
    return _paused && _started;
}