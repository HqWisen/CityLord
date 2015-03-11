#ifndef CITYLORDCLIENT_HPP_
#define CITYLORDCLIENT_HPP_

#include <iostream>
#include <string>
#include <time.h>

#include "../common/socket/ConnectionSocket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/lib/Map.hpp"
#include "../common/lib/Field.hpp"
#include "Updater.hpp"

class Updater;

#define CLIENTNAME "CityLord"
#define CINITEM "> "

class CityLordClient{
	ConnectionSocket connectionSocket;
    ConnectionSocket updateSocket;
    Map<ClientField>* map;
    Updater* updater;
	public:
		CityLordClient(char* hostname, int port);
		CityLordClient(const CityLordClient&) = default;
        ~CityLordClient();
		void run();
		void beginConnection();
		void login();
		void createAccount();
		void chooseCity();
		void createCity();
		void joinCity();
		void showMap();
		void selectField();
		void build();
		void showCatalog();
		void showInfo();
		void sendRequest(SocketMessage);
		void recvAnswer(SocketMessage&);
		int makeChoice(int min = 1, int max = 1);
        Map<ClientField>* getMap();
		void LOG(std::string);
};

#endif // CITYLORDCLIENT_HPP_

