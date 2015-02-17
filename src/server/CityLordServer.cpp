#include "CityLordServer.hpp"

const std::vector<std::string> CityLordServer::mapNameVector = {
	"Map1.txt",
	"Map2.txt",
	"Map3.txt"
};

CityLordServer::CityLordServer(int port) : serverSocket(port){}

void CityLordServer::run(){
	
	ClientSocket* clientSocketPtr;	
	
	LOG("Server is running...");
	serverSocket.listenClients();
	while(true){
		clientSocketPtr = serverSocket.acceptClient();
		LOG("A client with IP " + clientSocketPtr->getClientIP() + " is connected to " + SERVERNAME);
		// TODO désalloué quand un client se deconnecte
		new UserManager(this, *clientSocketPtr);
	}
}

void CityLordServer::createAccount(std::string username){
	if(!accountExist(username)){
		// TODO delete in destructor
		userMap.insert(std::map< std::string, User>::value_type(username, User(username)));
	}else{
		// TODO throw exception
	}
}

void CityLordServer::createCity(int number){
	cityManagerVector.push_back(CityManager(mapNameVector[number]));
}

bool CityLordServer::accountExist(std::string username){
	return userMap.find(username) != userMap.end();
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

const std::vector<std::string>& CityLordServer::getMapNameVector(){
	return mapNameVector;
}

