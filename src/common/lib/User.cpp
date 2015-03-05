#include "User.hpp"

User::User(std::string name, std::string pw) : username(name), password(pw){}

std::string User::getUserName(){
    return username;
}

std::string User::getPassword(){
    return password;
}

void User::initPlayer(CityManager* cm){
	if(playerMap.find(cm) == playerMap.end()){
		int id = cm->getNPlayer();
		playerMap[cm] = new Player(id, username);
		cm->addPlayer(playerMap[cm]);
	}
}
