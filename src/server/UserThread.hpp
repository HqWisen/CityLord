#ifndef USERTHREAD_HPP_
#define USERTHREAD_HPP_

#include "../common/thread/Thread.hpp"
#include "request/request.hpp"

#include <iostream>
#include <map>

class UserManager;

typedef void (* request_ptr)(SocketMessage *, CityLordServer *);

class UserThread : public Thread{
	static const std::map<std::string, request_ptr> requestMap;
	UserManager* userManager;
	public:
		UserThread(UserManager*);
		void run() override;
};

#endif // USERTHREAD_HPP_

