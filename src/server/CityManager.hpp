
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
#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <random>
#include "Generator.hpp"

int UPDATE_INTERVAL = 2;
int NUMBER_OF_VISITORS = 20;

class CityManager: public Thread{
	std::string mapname;
	Map cityMap; 
	int id;
	Catalog catalog;
	int nPlayer;
	Timer timer;
	unsigned long lastUpdateTime;

	std::vector<Spawnable> listSpawnable;
	//std::vector<Player*> playerVector;
	//std::vector<Visitor> listVisitor;
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

		std::vector<Location> giveWay();
		void run() override;
        Spawnable getRandomSpawn();

/*
	SocketMessage makeTrade(Player&, Player&, Location, int);
	std::string showCatalog();
	std::string showCity();
	void updateBuildings();
	void makeVisitorsAdvance();
	void spawnVisitors();
	void updateCity();
	*/
};

#endif

