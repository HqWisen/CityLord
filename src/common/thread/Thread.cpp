#include "Thread.hpp"

void* routine(void* data){
    Thread* threadPtr = (Thread*)data;
    threadPtr->setRunning(true);
    threadPtr->run();
    threadPtr->setRunning(false);
    pthread_exit(0);
}

Thread::Thread() : thread(), running(false){
}

void Thread::start(){
	pthread_create(&thread, NULL, routine, (void*)this);
}

void Thread::msleep(unsigned long ms){
    usleep(1000*ms);
}

void* Thread::join(){
	void* result;
	pthread_join(thread, &result);
	return result;
}

void Thread::cancel(){
    pthread_cancel(thread);
}

void Thread::setRunning(bool r){
    running = r;
}

bool Thread::isRunning(){
    return running;
}
