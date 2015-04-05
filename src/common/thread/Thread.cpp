#include "Thread.hpp"

void* routine(void* data){
    Thread* threadPtr = (Thread*)data;
	threadPtr->run();
	pthread_exit(0);
}

void Thread::start(){
	pthread_create(&thread, NULL, routine, (void*)this);
}

void* Thread::join(){
	void* result;
	pthread_join(thread, &result);
	return result;
}

void Thread::cancel(){
    pthread_cancel(thread);
}
