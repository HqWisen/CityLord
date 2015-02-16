#ifndef USERMANAGER_HPP_
#define USERMANAGER_HPP_

class CityLordServer;

class UserManager{
	CityLordServer* server;
	ClientSocket clientSocket;
	UserThread thread;
	public:
		UserManager(CityLordServer*, ClientSocket);
		void recvRequest(SocketMessage&);
		
};

#endif // USERMANAGER_HPP_

