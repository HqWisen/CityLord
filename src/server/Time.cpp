#include "Time.hpp"

const int Time::MINPERSEC = 5;
const int Time::MAXDAY = 15;


Time::Time(func_ptr func, int sleeptime, time_t* current){
    /**
     * Current is number of seconds since 1 Jan 1970
     * Default is 1 Jan 2015 00:00:00 */
    this->func = func;
    this->sleeptime = sleeptime;
    this->current = current == nullptr ? 1420066800 : *current;
}

void Time::run(){
    while(!over()){
        if (func) func();
        addMinute(MINPERSEC);
        secsleep(sleeptime);
    }
}

bool Time::over(){
    return getYDayNumber() >= MAXDAY;
}

void Time::addSecond(int second){
    current += second;
}

void Time::addMinute(int minute){
    addSecond(minute * 60);
}

void Time::secsleep(int second){
    usleep(1000000 * second); // microsecond
}

std::string Time::strtime(){
    return ctime(&current);
}

std::string Time::toString(){
    return std::to_string(current);
}

int Time::getYDayNumber(){
    return localtime(&current)->tm_yday;
}

int Time::getSleeptime(){
    return sleeptime;
}

void Time::setSleeptime(int time){
    sleeptime = time;
}

Time Time::parseTime(std::string parse){
    time_t now = std::stod(parse);
    return Time(nullptr, 1, &now);
}
