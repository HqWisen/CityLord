
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>
#include <pthread.h>
#include <unistd.h>

class Timer : public Thread{

	int (*functionPtr)(int,int);
	int waitingTime;
	unsigned long startTime;

	public:
		Timer(int, int (*)(int, int));
		void run();
		void start();
		unsigned long elapsedTime();
        bool isTimeout(unsigned long seconds);
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
