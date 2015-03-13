#ifndef CITYLORDSERVER_HPP_
#define CITYLORDSERVER_HPP_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <time.h>

#include "../common/socket/ServerSocket.hpp"
#include "../common/socket/ClientSocket.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "CityManager.hpp"

#define SERVERNAME "CityLordServer"

class CityLordServer{
    int port;
    ServerSocket serverSocket;
    ServerSocket updateClientSocket;
	std::map<std::string, User> userMap;
	static const std::vector<std::string> mapNameVector;
	std::vector<CityManager*> cityManagerVector;
	//std::map<std::string, UserThread> threadMap;
	//std::list<City> cityList;
	//std::list<User> userList;
	public:
		CityLordServer(int port);
		CityLordServer(const CityLordServer&) = default;
        ~CityLordServer();
		void run();
        User* createAccount(std::string, std::string);
		bool accountExist(std::string);
        bool matchPassword(std::string, std::string);
        CityManager* createCity(int, User*);
		CityManager* getCity(int);
		int getNumberOfCity();
		User* getUser(std::string);
        int getPort();
		void LOG(std::string);
		static const std::vector<std::string>& getMapNameVector();

};

#endif // CITYLORDSERVER_HPP_

