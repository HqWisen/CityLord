
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
#include "../common/lib/Map.hpp"
#include "../common/lib/Catalog.hpp"
#include "../common/lib/Spawnable.hpp"
#include "../common/lib/Visitor.hpp"
#include "CityUpdater.hpp"

class CityManager{
	std::string mapname;
	Map cityMap; 
	int id;
	Catalog catalog;
	int nPlayer;
	std::vector<Spawnable> listSpawnable;
	public:
		CityManager(std::string, int);
		std::string getMapName();
		int getID();
		int getNPlayer();
		void addPlayer(Player*);
		Map* getMap();
		std::vector<Field*> getPurchasableFields();
		SocketMessage makePurchase(Player*, Location);
		SocketMessage buildBuilding(Player*, Location, BuildingType);
		SocketMessage upgradeBuilding(Player*, Location);
		SocketMessage destroyBuilding(Player*, Location);

		std::vector<Location> giveWay();
        Spawnable getRandomSpawn();

/*
	SocketMessage makeTrade(Player&, Player&, Location, int);
	std::string showCatalog();
	std::string showCity();
	*/
};

#endif

