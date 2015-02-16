#include "UserThread.hpp"


const std::map<std::string, std::request_ptr> UserThread::requestMap = {
	{"login", request::login}
};

UserThread::UserThread(CityLordServer* cserver, ClientSocket socket) : server(cserver), clientSocket(socket){
	

}

void UserThread::run(){
	SocketMessage request;
	//while(request.getTopic() != QUIT_REQUEST){
		recvRequest(request);
		
		std::cout<<request.toString()<<std::endl;
				
	//}
}

void UserThread::recvRequest(SocketMessage& request){
 	request = SocketMessage::parse(clientSocket.read());
}

/*
void UserThread::beginConnection(){
	int choice = clientSocket.readInt();
	if(choice == M_LOGIN){
		login();
	}else if(choice == M_ACCOUNT){
		createAccount();
	}
}*/
/*
void UserThread::login(){
	bool fail = true;
	std::string nickname;
	while(fail){
		nickname = clientSocket.read();		
		if(server->accountExist(nickname)){
			server->LOG("Client with IP " + clientSocket.getClientIP() + " log in with account : " + nickname + ".");
			clientSocket.writeInt(SUCCESS);
			fail = false;
		}else{
			clientSocket.writeInt(FAIL);
		}
	}
}

void UserThread::createAccount(){
	bool fail = true;
	std::string nickname;
	while(fail){
		nickname = clientSocket.read();		
		if(!server->accountExist(nickname)){
			server->createAccount(nickname);
			clientSocket.writeInt(SUCCESS);
			server->LOG("Client with IP " + clientSocket.getClientIP() + " has created an account : " + nickname + ".");
			fail = false;
		}else{
			clientSocket.writeInt(FAIL);
		}
	}
}

*/

