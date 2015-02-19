#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Player.hpp"

Player::Player(string name,int nbr){
	userName=name;
	number=nbr;


	string colornumber;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << number+40;      // 40 if first player is player 0
	colornumber = convert.str(); // set 'colornumber' to the contents of the stream
	color="\033[1;"+colornumber+"m";

	//  \033[1;41m  red    		\033[1;42m  green   \033[1;43m   yellow    
	//  \033[1;44m  dark blue   \033[1;45m  purple  \033[1;46m   light blue  
	//  \033[1;40m   dark grey   \033[1;47m  white  

}

//bool Player::isBankrupt(){return money<0;}


//std::vector<Building*> Player::getOwnedBuildings(){return buildingList;}
//std::vector<Field*> Player::getOwnedFields(){return fieldList;}
//void Player::addField(Field field){fieldList.push_back(field);}
//void Player::addBuilding(Building building){BuildingList.push_back(building);}
void Player::loseMoney(int amount){money-=amount;}