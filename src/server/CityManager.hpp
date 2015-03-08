
#ifndef CITYMANAGER_HPP_
#define CITYMANAGER_HPP_

#include <iostream>
#include <string>
#include <cstdlib>

// A être inclus dans le fichier du serveur
/*
#include "../common/lib/Building.hpp"
#include "../common/lib/BuildingType.hpp"
#include "../common/lib/Case.hpp"
#include "../common/lib/City.hpp"
#include "../common/lib/Field.hpp"
#include "../common/lib/Neighborhood.hpp"
#include "../common/lib/Obstacle.hpp"
#include "../common/lib/Player.hpp"
#include "../common/lib/Road.hpp"
#include "../common/lib/User.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/lib/Location.hpp"
*/
//#include "../common/lib/Map.hpp"
#include "../common/lib/Catalog.hpp"
//#include "../common/lib/Spawnable.hpp"
//#include "../common/lib/Visitor.hpp"
#include "CityUpdater.hpp"
#include <vector>
#include <algorithm>

// Relative path of the executable
#define MAPFILEPATH "src/resources/maps/"

class User;

class CityManager{

    static const int DEFAULTMAXPLAYER;

    std::string mapname;
    Map<Field> cityMap;
	int id;
    User* creator;
	Catalog catalog;
	int nPlayer;
    std::vector<Player*> playerVector;
    const int MAXPLAYER;
    //std::vector<Spawnable> listSpawnable;
	public:
        CityManager(std::string, int, User*);
        std::string getMapName();
        std::string getMapFileName();
        int getID();
		int getNPlayer();
        int getMaxPlayer();
        int getNextID();
		void addPlayer(Player*);
        Map<Field>* getMap();
        User* getCreator();
        std::string getName();
        bool canJoin(Player*);
        bool alreadyInCity(Player*);
		std::vector<Field*> getPurchasableFields();
		SocketMessage makePurchase(Player*, Location);
		SocketMessage buildBuilding(Player*, Location, BuildingType);
		SocketMessage upgradeBuilding(Player*, Location);
		SocketMessage destroyBuilding(Player*, Location);

		std::vector<Location> giveWay();
        //Spawnable getRandomSpawn();
};

#endif

