#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "Location.hpp"
//#include "City.hpp"

using namespace std;

class Player{
	static Player* playerList[8];

	const int INITIALBUDGET = 150000;
	int money;
	int playerID;
	vector<Location> buildingList;
	vector<Location> fieldList;
	//City* city;
	string userName;
	string color; /* \033[1;40m   dark grey  \033[1;41m red    \033[1;42m  green   
					 \033[1;43m   yellow     \033[1;44m   dark blue
					 \033[1;45m   purple     \033[1;46m    light blue
					 \033[1;47m  white*/
public:
	//Player() = default;
	Player(string,int);
	void createBuilding();
	void removeBuilding();
	void makeOffer();
	void cancelOffer();
	void isBankrupt();
	string getColor();
	int getPlayerID();
	static Player* getPlayerByID(int); //De la part de Gab: SA MERE A CELUI QUI TOUCHE A CETTE FONCTION x(
	//std::vector<Location> getOwnedBuildings();
	//std::vector<Location> getOwnedFields();
	//void addField(Field);
	//void addBuilding(Building);
	void loseMoney(int);
};

#endif // PLAYER_HPP_

