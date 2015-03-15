#ifndef USERMANAGER_HPP_
#define USERMANAGER_HPP_

#include <pthread.h>
#include "../common/socket/ClientSocket.hpp"
#include "../common/socket/ServerSocket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/thread/Thread.hpp"
#include "request/request.hpp"
#include "User.hpp"
#include "CityManager.hpp"

class SocketMessage;
class UserManager;
class CityLordServer;
class CityManager;
class User;

typedef SocketMessage (* request_ptr)(CityLordServer*, UserManager *, SocketMessage);

class UserManager : public Thread{

	static const std::map<std::string, request_ptr> requestmap;

    CityLordServer* server = nullptr;
    ClientSocket clientSocket;
    ClientSocket* updateSocket;
    User* user = nullptr;
    CityManager* cityManager = nullptr;
    pthread_mutex_t updatemutex;
	public:
        UserManager(CityLordServer*, ClientSocket, ServerSocket);
		void run() override;
		void setUser(User*);
        User* getUser();
		void setActiveCity(CityManager*);
        void initActivePlayer(int);
		Player* getActivePlayer();
		CityManager* getActiveCity();
		std::string getIP();
		std::string getUserName();
        void disconnectUser();
		void recvRequest(SocketMessage&);
		void sendAnswer(SocketMessage);
        void sendUpdate(SocketMessage);
};

#endif // USERMANAGER_HPP_

