#ifndef Timer_HPP_
#define Timer_HPP_

#include <time.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "../thread/Thread.hpp"

typedef void (*func_ptr)(void*);

template <typename T>
class Timer : public Thread{
    static const int MINPERSLEEP, MAXDAY;
    T* object;
    func_ptr func;
    int sleepTime;
    time_t current;
    public:
    Timer(T*, int = 1, time_t* = nullptr);
    void run() override;
    bool over();
    void addSecond(int);
    void addMinute(int);
    void secsleep(int);
    int getYDayNumber();
    int getCurrentTime();
    func_ptr getFunc();
    void setFunc(func_ptr);
    T* getObject();
    void setObject(T*);
    int getSleeptime();
    void setSleeptime(int);
    std::string strtime();
    std::string toString();
    static Timer parseTimer(std::string);
};

/*** DEFINITION ***/

template <typename T>
const int Timer<T>::MINPERSLEEP = 30;
template <typename T>
const int Timer<T>::MAXDAY = 18;

template <typename T>
Timer<T>::Timer(T* obj, int sleepTime, time_t* current) : object(obj), func(nullptr){
    /**
     * Current is number of seconds since 1 Jan 1970
     * Default is 1 Jan 2015 00:00:00 */
    this->sleepTime = sleepTime;
    this->current = current == nullptr ? 1420066800 : *current;
}

template <typename T>
void Timer<T>::run(){
    while(!over()){
        if (func) func(object);
        addMinute(MINPERSLEEP);
        if(sleepTime == 0){
            usleep(450000); // microsecond
        }else{
            secsleep(sleepTime);
        }
    }
}

template <typename T>
bool Timer<T>::over(){
    return getYDayNumber() >= MAXDAY;
}

template <typename T>
void Timer<T>::addSecond(int second){
    current += second;
}

template <typename T>
void Timer<T>::addMinute(int minute){
    addSecond(minute * 60);
}

template <typename T>
void Timer<T>::secsleep(int second){
    usleep(1000000 * second); // microsecond
}

template <typename T>
std::string Timer<T>::strtime(){
    char buff[40];
    strftime(buff, 40, "%d-%m-%Y %H:%M:%S", localtime(&current));
    return buff;
    //return ctime(&current);
}

template <typename T>
std::string Timer<T>::toString(){
    return std::to_string(current);
}

template <typename T>
int Timer<T>::getYDayNumber(){
    return localtime(&current)->tm_yday;
}

template <typename T>
int Timer<T>::getCurrentTime(){
    return current;
}

template <typename T>
func_ptr Timer<T>::getFunc(){
    return func;
}

template <typename T>
void Timer<T>::setFunc(func_ptr foo){
    func = foo;
}

template <typename T>
T* Timer<T>::getObject(){
    return object;
}

template <typename T>
void Timer<T>::setObject(T* obj){
    object = obj;
}

template <typename T>
int Timer<T>::getSleeptime(){
    return sleepTime;
}

template <typename T>
void Timer<T>::setSleeptime(int time){
    sleepTime = time;
}

template <typename T>
Timer<T> Timer<T>::parseTimer(std::string parse){
    //std::cout<<"string to parse = "<<parse<<std::endl;
    time_t now = std::stod(parse);
    //std::cout<<"HELLO"<<std::endl;
    return Timer<T>(nullptr, 1, &now);
}

#endif // Timer_HPP_

