#include "Timer.hpp"


Timer::Timer(int timeWanted, int * (*pointerFunction)()){
		waitingTime = timeWanted;
		functionPtr = pointerFunction;
}

void Timer::run(){
	bool end = false;
	while(not end){
		*functionPtr;
		sleep(waitingTime);
	}
}


/*

void Timer::start(){
	startTime = clock();

}

unsigned long Timer::elapsedTime(){
     return ((unsigned long) clock() - startTime) / CLOCKS_PER_SEC;
}

bool Timer::isTimeout(unsigned long seconds){
	return seconds >= elapsedTime();
}

*/

