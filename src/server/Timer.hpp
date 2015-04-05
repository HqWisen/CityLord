
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include "../common/thread/Thread.hpp"

class Timer : public Thread{

	int * (*functionPtr)();
	int waitingTime;
	unsigned long startTime;

	public:
		Timer();
		Timer(int, int * (*)());
		void run();
        /*
		void start();
		unsigned long elapsedTime();
        bool isTimeout(unsigned long seconds);
        */
};

/*
class Timer {
    private:
        unsigned long startTime;
    public:
        void start();
        unsigned long elapsedTime();
        bool isTimeout(unsigned long seconds);
};
*/

#endif
