
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

class CityManager{
	std::string mapname;
	Map cityMap; 
	int id;
	Catalog catalog;
	int nPlayer;
	//std::vector<Player*> playerVector;
	public:
		CityManager(std::string, int);
		std::string getMapName();
		int getID();
		int getNPlayer();
		void addPlayer(Player*);
		Map* getMap();
		std::vector<Field*> getPurchasableFields();
		SocketMessage makePurchase(Player*, Location); //Implique que les coordonnées de la case sont envoyées du client vers le serveur et ont été décodées
		SocketMessage buildBuilding(Player*, Location, BuildingType);
		SocketMessage upgradeBuilding(Player*, Location);
		SocketMessage destroyBuilding(Player*, Location);
		
/*
	SocketMessage makeTrade(Player&, Player&, Location, int);
	std::string showCatalog();
	std::string showCity();
	void updateBuildings();
	*/
};

#endif

