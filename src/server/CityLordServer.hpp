#ifndef CITYLORDSERVER_HPP_
#define CITYLORDSERVER_HPP_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <time.h>

#include "../common/socket/ServerSocket.hpp"
#include "../common/socket/ClientSocket.hpp"
#include "../common/lib/User.hpp"
#include "UserManager.hpp"
#include "CityManager.hpp"

#define SERVERNAME "CityLordServer"

// Relative path of the executable
#define MAPFILEPATH "src/resources/maps/"

class CityLordServer{
	ServerSocket serverSocket;
	std::map<std::string, User> userMap;
	static const std::vector<std::string> mapNameVector;
	std::vector<CityManager*> cityManagerVector;
	//std::map<std::string, UserThread> threadMap;
	//std::list<City> cityList;
	//std::list<User> userList;
	public:
		CityLordServer(int port);
		CityLordServer(const CityLordServer&) = default;
		void run();
		User* createAccount(std::string);
		CityManager* createCity(int);
		CityManager* getCity(int);
		int getNumberOfCity();
		bool accountExist(std::string);
		User* getUser(std::string);

		//void login();
		//void logout();
		//void connect(City&, Player&);
		void LOG(std::string);
		static const std::vector<std::string>& getMapNameVector();

};

#endif // CITYLORDSERVER_HPP_

