#include <iostream>
#include <sstream>

#include "Player.hpp"

using namespace std;

Player* Player::playerList[8] = {nullptr};

Player::Player(int number, string nn){
	playerID = number;
	nickname = nn;
	string colornumber;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << number+40;      // 40 if first player is player 0
	colornumber = convert.str(); // set 'colornumber' to the contents of the stream
	color="\033[1;"+colornumber+"m"; /*  \033[1;40m   dark grey  \033[1;41m red    \033[1;42m  green   
										 \033[1;43m   yellow     \033[1;44m   dark blue
										 \033[1;45m   purple     \033[1;46m    light blue
										 \033[1;47m  white*/
	playerList[number] = this;
	money = INITIALBUDGET;
	nBuilding = 0;
}

int Player::getPlayerID(){
	return playerID;
}

string Player::getColor(){
	return color;
}

string Player::getNickName(){
	return nickname;
}

int Player::getMoney(){
	return money;
}
void Player::setMoney(int newMoney){
	money = newMoney;
}

Player* Player::getPlayerByID(int index){
	return playerList[index];
}
void Player::addField(Field* field){
	fieldVector.push_back(field);
}

void Player::createBuilding(Field* field){
	nBuilding++;
}

int Player::getNBuilding(){
	return nBuilding;
}

int Player::getNEmptyField(){
	return fieldVector.size() - nBuilding;
}

/*
//bool Player::isBankrupt(){return money<0;}


//std::vector<Building*> Player::getOwnedBuildings(){return buildingList;}
//std::vector<Field*> Player::getOwnedFields(){return fieldList;}
//void Player::addBuilding(Building building){BuildingList.push_back(building);}
void Player::loseMoney(int amount){
	money -= amount;
}

*/
