#ifndef CITYLORDCLIENT_HPP_
#define CITYLORDCLIENT_HPP_

#include <iostream>
#include <string>
#include <time.h>

#include "../common/socket/ConnectionSocket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/models/Map.hpp"
#include "../common/models/Field.hpp"
#include "ClientManager.hpp"

#define CLIENTNAME "CityLord"
#define CINITEM "> "

class CityLordClient{
    ClientManager* clientManager;
	public:
        CityLordClient(char* hostname, int port);
		CityLordClient(const CityLordClient&) = default;
        ~CityLordClient();
		void runClient();
		void beginConnection();
		void login();
		void createAccount();
		void chooseCity();
		void createCity();
		void joinCity();
		void showMap();
		void selectField();
		void showCatalog();
		void showInfo();
		int makeChoice(int min = 1, int max = 1);
		void LOG(std::string);
};

#endif // CITYLORDCLIENT_HPP_

