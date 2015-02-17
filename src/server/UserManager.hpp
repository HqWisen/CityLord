#ifndef USERMANAGER_HPP_
#define USERMANAGER_HPP_

#include "../common/socket/ClientSocket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/thread/Thread.hpp"
#include "request/request.hpp"

class SocketMessage;
class UserManager;
class CityLordServer;

typedef SocketMessage (* request_ptr)(CityLordServer*, UserManager *, SocketMessage);
//typedef void (* view_ptr)(JsonValue *, UserHandler *);
class UserManager : public Thread{
	static const std::map<std::string, request_ptr> requestmap;

	CityLordServer* server;
	ClientSocket clientSocket;
	public:
		UserManager(CityLordServer*, ClientSocket);
		void recvRequest(SocketMessage&);
		void sendAnswer(SocketMessage);
		std::string getIP();
		void run() override;
};

#endif // USERMANAGER_HPP_

