#include "UserManager.hpp"

const std::map<std::string, request_ptr> UserManager::requestmap = {
	{"login", request::login},
	{"createaccount", request::createaccount},
	{"choicemap", request::choicemap},
	{"createcity", request::createcity},
    {"cityinfo", request::cityinfo},
	{"joincity", request::joincity},
	{"selectfield", request::selectfield},
	{"showinfo", request::showinfo},
	{"showcatalog", request::showcatalog},
	{"buy", request::buy},
	{"build", request::build},
	{"upgrade", request::upgrade},
	{"destroy", request::destroy}
};

UserManager::UserManager(CityLordServer* cserver, ClientSocket socket, ServerSocket updateClientSocket) : server(cserver), clientSocket(socket), \
    updateSocket(nullptr){
    SocketMessage answer;
    answer.setTopic("update");
    sendAnswer(answer);
    updateSocket = updateClientSocket.acceptClient();
    this->start();
}

void UserManager::run(){
	SocketMessage request, answer;
    recvRequest(request);
	while(request.getTopic() != "quit" and !request.getTopic().empty()){
		answer = UserManager::requestmap.at(request.getTopic())(server, this, request);
		sendAnswer(answer);
		recvRequest(request);
	}
    user->getPlayer(cityManager)->setConnected(false);
    user->getPlayer(cityManager)->setUserManager(nullptr);
    setActiveCity(nullptr);
    server->LOG("User '"+getUserName()+"' with IP "+clientSocket.getClientIP()+" is now disconnected.");
}

void UserManager::setUser(User* user_){
    user = user_;
}

User* UserManager::getUser(){
    return user;
}

void UserManager::setActiveCity(CityManager* cm){
	cityManager = cm;
}

void UserManager::initActivePlayer(int playerid){
    user->initPlayer(cityManager, playerid);
    user->getPlayer(cityManager)->setConnected(true);
    user->getPlayer(cityManager)->setUserManager(this);
}

Player* UserManager::getActivePlayer(){
	return user->getPlayer(cityManager);
}

CityManager* UserManager::getActiveCity(){
	return cityManager;
}

std::string UserManager::getIP(){
	return clientSocket.getClientIP();
}

std::string UserManager::getUserName(){
    if(user != nullptr){
        return user->getUserName();
    }else{
        return "Unknown username";
    }
}

void UserManager::recvRequest(SocketMessage& request){
    request = SocketMessage::parse(clientSocket.read());
}

void UserManager::sendAnswer(SocketMessage answer){
    clientSocket.write(answer.toString());
}

void UserManager::sendUpdate(SocketMessage update){
    updateSocket->write(update.toString());
}



