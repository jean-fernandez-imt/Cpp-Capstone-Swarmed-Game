#ifndef TIMER_H
#define TIMER_H

#include <cstdlib>

//Synchronizes different events
class Timer {
    public:
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's current time
		std::size_t getTicks();

		bool isStarted();
		bool isPaused();

    private:
		std::size_t _startTicks;
		std::size_t _pausedTicks;

		bool _paused;
		bool _started;
};

#endif