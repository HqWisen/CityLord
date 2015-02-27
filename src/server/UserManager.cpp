#include "UserManager.hpp"

const std::map<std::string, request_ptr> UserManager::requestmap = {
	{"login", request::login},
	{"createaccount", request::createaccount},
	{"choicemap", request::choicemap},
	{"createcity", request::createcity},
	{"choicecity", request::choicecity},
	{"joincity", request::joincity},
	{"showmap", request::showmap},
	{"mapsize", request::mapsize},
	{"selectfield", request::selectfield},
	{"showinfo", request::showinfo},
	{"showcatalog", request::showcatalog},
	{"buy", request::buy},
	{"build", request::build},
	{"upgrade", request::upgrade},
	{"destroy", request::destroy}
};

UserManager::UserManager(CityLordServer* cserver, ClientSocket socket) : server(cserver), clientSocket(socket){
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
}

void UserManager::setUser(User* user_){
	user = user_;
}

void UserManager::setActiveCity(CityManager* cm){
	cityManager = cm;
}

void UserManager::initActivePlayer(){
	user->initPlayer(cityManager);
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
	return user->getUserName();
}

void UserManager::recvRequest(SocketMessage& request){
 	request = SocketMessage::parse(clientSocket.read());
}

void UserManager::sendAnswer(SocketMessage answer){
 	clientSocket.write(answer.toString());
}



