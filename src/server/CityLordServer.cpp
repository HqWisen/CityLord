#include "CityLordServer.hpp"

const std::vector<std::string> CityLordServer::mapNameVector = {
    "CITYBAY",
    "ROADRED",
    "EQUALAND"
};

CityLordServer::CityLordServer(int port_) : port(port_), serverSocket(port), updateClientSocket(port+1){}

CityLordServer::~CityLordServer(){
    // TODO Implement (delete usermanger and citymanager)
}


void CityLordServer::runServer(){
	
	ClientSocket* clientSocketPtr;	
	LOG("Server is running...");
	serverSocket.listenClients();
    updateClientSocket.listenClients();
	while(true){
		clientSocketPtr = serverSocket.acceptClient();
		LOG("A client with IP " + clientSocketPtr->getClientIP() + " is connected to " + SERVERNAME);
		// TODO désalloué quand un client se deconnecte
        new UserManager(this, *clientSocketPtr, updateClientSocket);
	}
}


User* CityLordServer::createAccount(std::string username, std::string password){
	if(!accountExist(username)){
		// TODO delete in destructor
        userMap.insert(std::map< std::string, User>::value_type(username, User(username, password)));
	}else{
        // TODO throw exception
	}
	return &(userMap[username]);
}

CityManager* CityLordServer::createCity(int numberOfMap, User* creator, Gamemode mode){
	// TODO Accès concurentielle
    // TODO server destructor
    cityManagerVector.push_back(new CityManager(mapNameVector[numberOfMap], cityManagerVector.size(), creator, mode));
	return cityManagerVector.back();
}

bool CityLordServer::accountExist(std::string username){
    return userMap.find(username) != userMap.end();
}

bool CityLordServer::matchPassword(std::string username, std::string password){
    return userMap[username].getPassword() == password;
}

CityManager* CityLordServer::getCity(int cityid){
    return cityManagerVector[cityid];
}

int CityLordServer::getNumberOfCity(){
	return cityManagerVector.size();
}

User* CityLordServer::getUser(std::string username){
	return &(userMap[username]);
}

int CityLordServer::getPort(){
    return port;
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

