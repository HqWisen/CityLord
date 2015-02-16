#ifndef USERTHREAD_HPP_
#define USERTHREAD_HPP_

#include "../common/thread/Thread.hpp"
#include "../common/socket/ClientSocket.hpp"
#include "CityLordServer.hpp"
#include "request/request.hpp"

#include <iostream>
#include <map>

class CityLordServer;

typedef void (* request_ptr)(SocketMessage *, CityLordServer *);

class UserThread : public Thread{
	CityLordServer* server;
	ClientSocket clientSocket;
	static const std::map<std::string, request_ptr> requestMap;
	public:
		UserThread(CityLordServer*, ClientSocket);
		void run() override;
		void recvRequest(SocketMessage&);
		
};

#endif // USERTHREAD_HPP_

