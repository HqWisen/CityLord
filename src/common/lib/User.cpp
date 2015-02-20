#include "User.hpp"

User::User(std::string name) : username(name){}

std::string User::getUserName(){
	return username;
}

void User::initPlayer(CityManager* cm){
	if(playerMap.find(cm) == playerMap.end()){
		playerMap[cm] = new Player();
	}
}
