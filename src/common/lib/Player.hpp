#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "Building.hpp"
#include "Field.hpp"
//#include "City.hpp"

class Player{
	const int INITIALBUDGET = 150000;
	int money;
	//std::vector<Building*> buildingList;
	//std::vector<Field*> fieldList;
	//City* city;
	int number;
	string userName;
	string color; //  \033[1;41m red    \033[1;42m  green   \033[1;43m   yellow    \033[1;44m   dark blue      \033[1;45m   purple    \033[1;46m    light blue    \033[1;40m   dark grey   \033[1;47m  white 
	
public:
	Player() = default;
	Player(string,int);
	void buildBuilding();
	void destroyBuilding();
	void makeOffer();
	void cancelOffer();
	void isBankrupt();
	//std::vector<Building*> getOwnedBuildings();
	//std::vector<Field*> getOwnedFields();
	//void addField(Field);
	//void addBuilding(Building);
	void loseMoney(int);
};

#endif // PLAYER_HPP_

