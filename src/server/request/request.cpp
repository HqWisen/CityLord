#include "request.hpp"

namespace request{
	void login(){
		UserManager*; SocketMessage message;
		message.get("username");

	}
	void buildBuilding(UserManager* um, SocketMessage message){
		CityManager* cm = um->getCityManager();		
		um->getPlayer();
		int x = std::stoi(message.get("x"));
		int y = std::stoi(message.get("y"));
		std::string type = std::stoi(message.get("type"));
		cm->buildBuilding(player, x, y, type);	
		S		
		um->sendAnswer();
}
}
