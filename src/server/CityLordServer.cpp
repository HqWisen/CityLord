#include "CityLordServer.hpp"


CityLordServer::CityLordServer(int port) : serverSocket(port){
}

void CityLordServer::run(){
	
	ClientSocket* clientSocketPtr;	
	
	LOG("Server is running...");
	serverSocket.listenClients();
	while(true){
		clientSocketPtr = serverSocket.acceptClient();
		LOG("Client " + clientSocketPtr->getClientIP() + " is connected to " + SERVERNAME);
		UserThread thread;
		thread.start();

	}
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
