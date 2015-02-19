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
		void chooseCity();
		void createAccount();
		void login();
		void createCity();
		void joinCity();
		int makeChoice(int min = 1, int max = 1);
		void sendRequest(SocketMessage);
		void recvAnswer(SocketMessage&);
		void LOG(std::string);
		void showMap();
		void selectField();
		//void build();
		//void showCatalog();
		//void showInfo();
		//void showInfoOthersPlayers();
};

#endif // CITYLORDCLIENT_HPP_

