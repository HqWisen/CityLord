#include "Timer.hpp"


void Timer::start(){
	startTime = clock();

}

unsigned long Timer::elapsedSecond(){
     return ((unsigned long) clock() - startTime) / CLOCKS_PER_SEC;
}

bool Timer::isTimeout(unsigned long seconds){
	return seconds >= elapsedTime();
}
