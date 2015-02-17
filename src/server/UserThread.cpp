#include "UserThread.hpp"
/*
const std::map<std::string, request_ptr> UserThread::requestMap = {
	{"login", request::login}
};
*/
UserThread::UserThread(UserManager* userManager_) : userManager(userManager_){};


void UserThread::run(){
	/*SocketMessage request;
	//while(request.getTopic() != QUIT_REQUEST){
		userManager->recvRequest(request);*/
		std::cout<<"request.toStrilkmjmljkng()"<<std::endl;
		//userManager->test();
	//}
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

