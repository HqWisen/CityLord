#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

class Thread{
	pthread_t thread;
    bool running;
    public:
        friend void* routine(void*);
    public:
        Thread();
        void start();
		virtual ~Thread() = default;
        void* join();
        void cancel();
        void msleep(unsigned long);
        bool isRunning();
        virtual void run() = 0;
    private:
        void setRunning(bool);
};

#endif // THREAD_HPP_

