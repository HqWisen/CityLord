#ifndef USERTHREAD_HPP_
#define USERTHREAD_HPP_

#include "../common/thread/Thread.hpp"

class UserThread : public Thread{
	public:
		void run() override;
};

#endif // USERTHREAD_HPP_

