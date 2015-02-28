
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>

class Timer {
    private:
        unsigned long startTime;
    public:
        void start();
        unsigned long elapsedTime();
        bool isTimeout(unsigned long seconds);
};

#endif