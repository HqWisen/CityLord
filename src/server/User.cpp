#include "User.hpp"

User::User(std::string name, std::string pw) : username(name), password(pw){}

std::string User::getUserName(){
    return username;
}

std::string User::getPassword(){
    return password;
}

void User::initPlayer(CityManager* cm, int playerid){
	if(playerMap.find(cm) == playerMap.end()){
        playerMap[cm] = new Player(playerid, username);
		cm->addPlayer(playerMap[cm]);
	}
}
