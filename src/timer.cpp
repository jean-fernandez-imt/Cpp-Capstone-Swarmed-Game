#include <SDL2/SDL.h>

#include "timer.h"

Timer::Timer() {
    _startTicks = 0;
    _pausedTicks = 0;

    _paused = false;
    _started = false;
}

void Timer::start() {
    _started = true;
    _paused = false;

    _startTicks = SDL_GetTicks();
	_pausedTicks = 0;
}

void Timer::stop() {
    _started = false;
    _paused = false;

	//Clear tick variables
	_startTicks = 0;
	_pausedTicks = 0;
}

void Timer::pause() {
    if(_started && !_paused) {
        _paused = true;

        //Calculate the paused ticks
        _pausedTicks = SDL_GetTicks() - _startTicks;
		_startTicks = 0;
    }
}

void Timer::unpause() {
    if(_started && _paused) {
        _paused = false;

        //Reset the starting ticks
        _startTicks = SDL_GetTicks() - _pausedTicks;

        //Reset the paused ticks
        _pausedTicks = 0;
    }
}

std::size_t Timer::getTicks() {
	std::size_t time = 0;

    if(_started) {
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
    return _started;
}

bool Timer::isPaused() {
    return _paused && _started;
}