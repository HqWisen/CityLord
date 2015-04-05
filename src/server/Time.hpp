#ifndef TIME_HPP_
#define TIME_HPP_

#include <time.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "../common/thread/Thread.hpp"

typedef void (* func_ptr)(void);


class Time : public Thread{
    static const int MINPERSEC, MAXDAY;
    int sleeptime;
    func_ptr func;
    time_t current;
    public:
    Time(func_ptr = nullptr, int = 1, time_t* = nullptr);
    void run() override;
    bool over();
    void addSecond(int);
    void addMinute(int);
    void secsleep(int);
    int getYDayNumber();
    int getSleeptime();
    void setSleeptime(int);
    std::string strtime();
    std::string toString();
    static Time parseTime(std::string);
};

#endif // TIME_HPP_

