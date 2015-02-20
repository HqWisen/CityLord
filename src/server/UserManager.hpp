#ifndef USERMANAGER_HPP_
#define USERMANAGER_HPP_

#include "../common/socket/ClientSocket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/thread/Thread.hpp"
#include "request/request.hpp"
#include "../common/lib/User.hpp"
#include "CityManager.hpp"

class SocketMessage;
class UserManager;
class CityLordServer;
class CityManager;
class User;

typedef SocketMessage (* request_ptr)(CityLordServer*, UserManager *, SocketMessage);
class UserManager : public Thread{
	static const std::map<std::string, request_ptr> requestmap;

	CityLordServer* server;
	ClientSocket clientSocket;
	User* user;
	CityManager* cityManager;
	public:
		UserManager(CityLordServer*, ClientSocket);
		void recvRequest(SocketMessage&);
		void sendAnswer(SocketMessage);
		std::string getIP();
		std::string getUserName();
		void setUser(User*);
		void setActiveCity(CityManager*);
		void initActivePlayer(){user->initPlayer(cityManager);};
		void run() override;
		CityManager* getActiveCity(){return cityManager;};
		Player* getActivePlayer(){return user->getPlayer(cityManager);};
};

#endif // USERMANAGER_HPP_

