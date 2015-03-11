#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "Location.hpp"
//#include "City.hpp"

using namespace std;

class Field;
class UserManager;

class Player{

    const int INITIALBUDGET = 150000;
	int money;
	int playerID;
	int nBuilding;
	//vector<Location> buildingList;
	vector<Field*> fieldVector;
	//City* city;
	string nickname;
    bool connected;
    UserManager* userManager;
public:
    static const string COLOR[8];
public:
	Player(int, string);
	int getPlayerID();
	string getNickName();
	int getNBuilding();
	int getNEmptyField();
	int getMoney();
	void setMoney(int);
    void addField(Field*);
	void buildBuilding();
	void destroyBuilding();
    bool isConnected();
    void setConnected(bool);
    UserManager* getUserManager();
    void setUserManager(UserManager*);
	
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

