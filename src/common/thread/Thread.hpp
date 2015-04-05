#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>

class Thread{
	pthread_t thread;
	public:
		Thread() = default;
		void start();
		virtual ~Thread() = default;
        void* join();
        void cancel();
		virtual void run() = 0;
		
};

#endif // THREAD_HPP_

