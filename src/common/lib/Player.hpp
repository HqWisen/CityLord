#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "Location.hpp"
//#include "City.hpp"

using namespace std;

class Field;

class Player{
	const int INITIALBUDGET = 150000;
	int money;
	int playerID;
	int nBuilding;
	//vector<Location> buildingList;
	vector<Field*> fieldVector;
	//City* city;
	string color; /* \033[1;40m   dark grey  \033[1;41m red    \033[1;42m  green   
					 \033[1;43m   yellow     \033[1;44m   dark blue
					 \033[1;45m   purple     \033[1;46m    light blue
					 \033[1;47m  white*/
	string nickname;
public:
	Player(int, string);
	string getColor();
	int getPlayerID();
	string getNickName();
	int getNBuilding();
	int getNEmptyField();
	int getMoney();
	void setMoney(int);
    void addField(Field*);
	void buildBuilding();
	void destroyBuilding();
	
	/*void createBuilding();
	void removeBuilding();
	void makeOffer();
	void cancelOffer();
	void isBankrupt();
	//std::vector<Location> getOwnedBuildings();
	//std::vector<Location> getOwnedFields();
	//void addBuilding(Building);
	void loseMoney(int);*/
};

#endif // PLAYER_HPP_

