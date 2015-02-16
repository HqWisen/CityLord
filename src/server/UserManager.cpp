#include "UserManager.hpp"

UserManager::UserManager(CityLordServer* cserver, ClientSocket socket) : server(cserver), clientSocket(socket), thread(this){
	thread.start();
}

void UserThread::recvRequest(SocketMessage& request){
 	request = SocketMessage::parse(clientSocket.read());
}



