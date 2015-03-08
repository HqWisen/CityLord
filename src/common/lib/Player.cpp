#include <iostream>
#include <sstream>

#include "Player.hpp"

using namespace std;


/**
 *
 * \033[1;40m dark grey   \033[1;41m   red
 * \033[1;42m green       \033[1;43m   yellow
 * \033[1;44m dark blue   \033[1;45m   purple
 * \033[1;46m light blue  \033[1;47m  white
*/
const string Player::COLOR[8] = {"\033[1;40m", "\033[1;41m", "\033[1;42m", "\033[1;43m", "\033[1;44m", "\033[1;45m", "\033[1;46m", "\033[1;47m"};

Player::Player(int number, string nn){
	playerID = number;
	nickname = nn;
    money = INITIALBUDGET;
	nBuilding = 0;
}

int Player::getPlayerID(){
	return playerID;
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

void Player::addField(Field* field){
	fieldVector.push_back(field);
}

int Player::getNBuilding(){
	return nBuilding;
}

int Player::getNEmptyField(){
	return fieldVector.size() - nBuilding;
}

void Player::buildBuilding(){
	nBuilding++;
}

void Player::destroyBuilding(){
	nBuilding--;
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
