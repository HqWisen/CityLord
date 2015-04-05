
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>
#include <pthread.h>

/*
class Timer : public Thread{

	int (*functionPtr)(int,int);
	int waitingTime;

	public:
		Timer(int, int*);
		void run();
};
*/


class Timer {
    private:
        unsigned long startTime;
    public:
        void start();
        unsigned long elapsedTime();
        bool isTimeout(unsigned long seconds);
};


#endif
