#include "request.hpp"

namespace request{
	
	SocketMessage login(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		if(server->accountExist(message.get("username"))){
			server->LOG("Client with IP " + userManager->getIP() + " log in with username " + message.get("username") + ".");
			answer.setTopic("success");
		}else{
			answer.setTopic("failure");
			answer.set("reason", "Login failed : this username doesn't exist.");
			
		}
		return answer;
	}

	SocketMessage createAccount(CityLordServer* server, UserManager* userManager, SocketMessage message){
		SocketMessage answer;
		if(!server->accountExist(message.get("username"))){
			server->createAccount(message.get("username"));
			server->LOG("Client with IP " + userManager->getIP() + " has created an account with username " + message.get("username") + ".");
			answer.setTopic("success");
		}else{
			answer.setTopic("failure");
			answer.set("reason", "Creation failure : This username is already used.");
		}
		return answer;		
	}
}
