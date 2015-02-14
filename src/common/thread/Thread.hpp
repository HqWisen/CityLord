#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>
#include <iostream>

class Thread{
	pthread_t thread;
	public:
		Thread() = default;
		void start();
		//void* join();
		virtual void run() = 0;
		
};

#endif // THREAD_HPP_
