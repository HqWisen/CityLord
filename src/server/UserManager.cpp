#include "UserManager.hpp"

const std::map<std::string, request_ptr> UserManager::requestmap = {
	{"login", request::login},
	{"createaccount", request::createaccount},
	{"choicemap", request::choicemap},
	{"createcity", request::createcity}
};

UserManager::UserManager(CityLordServer* cserver, ClientSocket socket) : server(cserver), clientSocket(socket){
	this->start();
}

void UserManager::recvRequest(SocketMessage& request){
 	request = SocketMessage::parse(clientSocket.read());
}

void UserManager::sendAnswer(SocketMessage answer){
 	clientSocket.write(answer.toString());
}

std::string UserManager::getIP(){
	return clientSocket.getClientIP();
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



