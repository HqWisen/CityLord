#ifndef CITYLORDCLIENT_HPP_
#define CITYLORDCLIENT_HPP_

#include <iostream>
#include <string>
#include <time.h>
#include "../common/socket/ConnectionSocket.hpp"
#include "../common/lib/common.h"

#define CLIENTNAME "CityLord"
#define CINITEM "> "

class CityLordClient{
	ConnectionSocket connectionSocket;
	public:
		CityLordClient(char* hostname, int port);
		CityLordClient(const CityLordClient&) = default;
		void run();
		void beginConnection();
		void createAccount();
		void login();
		int makeChoice(int min = 1, int max = 1);
		void LOG(std::string);
};

#endif // CITYLORDCLIENT_HPP_

