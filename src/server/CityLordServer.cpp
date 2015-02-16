#include "CityLordServer.hpp"


CityLordServer::CityLordServer(int port) : serverSocket(port){}

void CityLordServer::run(){
	
	ClientSocket* clientSocketPtr;	
	UserManager* userManager;
	
	LOG("Server is running...");
	serverSocket.listenClients();
	while(true){
		clientSocketPtr = serverSocket.acceptClient();
		LOG("A client with IP " + clientSocketPtr->getClientIP() + " is connected to " + SERVERNAME);
		// TODO désalloué quand un client se deconnecte
		userManager = new UserManager(this, *clientSocketPtr);
	}
}

void CityLordServer::createAccount(std::string nickname){
	if(!accountExist(nickname)){
		User user;
		userMap[nickname] = user;
	}else{
		// TODO throw exception
	}
}

bool CityLordServer::accountExist(std::string nickname){
	return userMap.find(nickname) != userMap.end();
}

void CityLordServer::LOG(std::string info){
	time_t now = time(0);
	struct tm tstruct;
	char timestr[80];
	tstruct = *localtime(&now);
  //strftime(timestr, sizeof(timestr), "%d-%m-%Y, %X", &tstruct); // with date
  strftime(timestr, sizeof(timestr), "%X", &tstruct);
	std::cout<<"["<<SERVERNAME<<"]";
	std::cout<<"["<<timestr<<"]";
	std::cout<<" ";
	std::cout<<info;
	std::cout<<std::endl;
}
