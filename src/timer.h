#ifndef TIMER_H
#define TIMER_H

#include <cstdlib>

class Timer {
    public:
		//Initializes variables
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		std::size_t getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		std::size_t _startTicks;

		//The ticks stored when the timer was paused
		std::size_t _pausedTicks;

		//The timer status
		bool _paused;
		bool _started;
};

#endif