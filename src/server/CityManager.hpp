
#ifndef CITYMANAGER_HPP_
#define CITYMANAGER_HPP_

#include <iostream>
#include <string>
#include <cstdlib>

#include "../common/lib/Catalog.hpp"
#include "CityUpdater.hpp"
#include <vector>
#include <algorithm>

// Relative path of the executable
#define MAPFILEPATH "src/resources/maps/"

class User;

class CityManager{

    static const int DEFAULTMAXPLAYER;

    std::string mapname;
    Map<Field>* cityMap;
    CityUpdater* updater;
	int id;
    User* creator;
	Catalog catalog;
	int nPlayer;
    std::vector<Player*> playerVector;
    const int MAXPLAYER;
    //std::vector<Spawnable> listSpawnable;
	public:
        CityManager(std::string, int, User*);
        ~CityManager();
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
        void sendUpdateToPlayers(SocketMessage);

		std::vector<Location> giveWay();
        //Spawnable getRandomSpawn();
};

#endif

