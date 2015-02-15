#include "UserThread.hpp"
UserThread::UserThread(CityLordServer* cserver, ClientSocket socket) : server(cserver), clientSocket(socket){}

void UserThread::run(){
	beginConnection();
}

void UserThread::beginConnection(){
	std::string choicestr = clientSocket.read();
	int choice = std::stoi(choicestr);
	if(choice == M_LOGIN){
	}else if(choice == M_ACCOUNT){
		bool fail = true;
		while(fail){
			std::string nickname = clientSocket.read();		
			if(!server->accountExist(nickname)){
				server->createAccount(nickname);
				clientSocket.write(SUCCESS);
				server->LOG("Client with IP " + clientSocket.getClientIP() + " has created an account : " + nickname);
				fail = false;
			}else{
				server->LOG("Client with IP " + clientSocket.getClientIP() + " try to create accout : " + nickname + ", but it already exist");
				clientSocket.write(FAIL);
			}
		}
	}
}

