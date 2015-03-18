#include <iostream>
#include <sstream>

#include "Player.hpp"
#include "UserManager.hpp"

using namespace std;


/**
 *
 * \033[1;40m dark grey   \033[1;41m   red
 * \033[1;42m green       \033[1;43m   yellow
 * \033[1;44m dark blue   \033[1;45m   purple
 * \033[1;46m light blue  \033[1;47m  white
*/
const int Player::INITIALBUDGET = 1000000;
const string Player::COLOR[8] = {"\033[1;40m", "\033[1;41m", "\033[1;42m", "\033[1;43m", "\033[1;44m", "\033[1;45m", "\033[1;46m", "\033[1;47m"};
const string Player::COLORNAME[8] = {"darkgrey", "red", "green", "yellow", "darkblue", "purple", "lightblue", "white"};

Player::Player(int number, string nn){
	playerID = number;
	nickname = nn;
    money = INITIALBUDGET;
    buildingCounter = 0;
    connected = false;
    userManager = nullptr;
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
    /*SocketMessage update("updatemoney");
    update.set("money", std::to_string(money));
    userManager->sendUpdate(update);*/
}

void Player::gainMoney(int amount){
    setMoney(money + amount);
}

void Player::loseMoney(int amount){
    setMoney(money - amount);
}

void Player::addField(Field* field){
    fieldVector.push_back(field);
}

void Player::incBuildingCounter(){
    buildingCounter++;
}

void Player::decBuildingCounter(){
    buildingCounter--;
}

bool Player::isConnected(){
    return connected;
}

void Player::setConnected(bool c){
    connected = c;
}

UserManager* Player::getUserManager(){
    return userManager;
}

void Player::setUserManager(UserManager* um){
    userManager = um;
}

int Player::getNBuilding(){
    return buildingCounter;
}

int Player::getNEmptyField(){
    return fieldVector.size() - buildingCounter;
}
