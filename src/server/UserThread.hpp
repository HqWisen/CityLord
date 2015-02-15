#ifndef USERTHREAD_HPP_
#define USERTHREAD_HPP_

#include "../common/thread/Thread.hpp"
#include "../common/socket/ClientSocket.hpp"
#include "CityLordServer.hpp"

#include <iostream>

class CityLordServer;

class UserThread : public Thread{
	CityLordServer* server;
	ClientSocket clientSocket;
	public:
		UserThread(CityLordServer*, ClientSocket);
		void run() override;
		void beginConnection();
		void login();
		void createAccount();
		
};

#endif // USERTHREAD_HPP_

