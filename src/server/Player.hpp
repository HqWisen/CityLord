#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "../common/models/Location.hpp"

using namespace std;

class Field;
class UserManager;

class Player{

    static const int INITIALBUDGET;
    int playerID;
    string nickname;
    vector<Field*> fieldVector;
    int money;
    int buildingCounter;
    bool connected;
    UserManager* userManager;
public:
    static const string COLOR[8], COLORNAME[8];
public:
	Player(int, string);
    int getPlayerID();
    string getNickName();
    int getMoney();
    void setMoney(int);
    void gainMoney(int);
    void loseMoney(int);
    void addField(Field*);
    void removeField(Field*);
    void incBuildingCounter();
    void decBuildingCounter();
    bool isConnected();
    void setConnected(bool);
    UserManager* getUserManager();
    void setUserManager(UserManager*);
    int getNBuilding();
    int getNEmptyField();
};

#endif // PLAYER_HPP_

