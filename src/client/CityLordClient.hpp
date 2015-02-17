#ifndef CITYLORDCLIENT_HPP_
#define CITYLORDCLIENT_HPP_

#include <iostream>
#include <string>
#include <time.h>

#include "../common/socket/ConnectionSocket.hpp"
#include "../common/socket/SocketMessage.hpp"


#define CLIENTNAME "CityLord"
#define CINITEM "> "

class CityLordClient{
	ConnectionSocket connectionSocket;
	public:
		CityLordClient(char* hostname, int port);
		CityLordClient(const CityLordClient&) = default;
		void run();
		void beginConnection();
		void login();
		void createAccount();
		int makeChoice(int min = 1, int max = 1);
		void sendRequest(SocketMessage);
		void recvAnswer(SocketMessage&);
		void LOG(std::string);
};

#endif // CITYLORDCLIENT_HPP_

