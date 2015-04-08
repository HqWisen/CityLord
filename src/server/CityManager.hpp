
#ifndef CITYMANAGER_HPP_
#define CITYMANAGER_HPP_

#include <iostream>
#include <string>
#include <cstdlib>

#include "Catalog.hpp"
#include "CityUpdater.hpp"
#include <vector>
#include <algorithm>

// Relative path of the executable
#define MAPFILEPATH "src/resources/maps/"

class User;

class CityManager{

    static const int DEFAULTMAXPLAYER;

    Gamemode mode;
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

        static const int ROADBLOCKPRICE = 200000;

        CityManager(std::string, int, User*, Gamemode);
        ~CityManager();
        std::string getMapName();
        std::string getMapFileName();
        std::string getStringTimer();
        int getID();
		int getNPlayer();
        int getMaxPlayer();
        int getNextID();
		void addPlayer(Player*);
        Map<Field>* getMap();
        //std::vector<Player*>* getPlayerVector();
        User* getCreator();
        std::string getName();
        bool canJoin(Player*);
        bool alreadyInCity(Player*);
        //void sendVisitorsFor(UserManager*);
		std::vector<Field*> getPurchasableFields();
		std::vector<Offer*> getOffers();
        int getRoadBlockPrice();
        float getDifficultyMultiplier();
        float getAdvantageMultiplier();
		SocketMessage makePurchase(Player*, Location);
		SocketMessage buildBuilding(Player*, Location, BuildingType);
		SocketMessage upgradeBuilding(Player*, Location);
		SocketMessage destroyBuilding(Player*, Location);
        SocketMessage offer(Player*, Location, int);
        SocketMessage acceptOffer(Player*, Location);
        SocketMessage cancelOffer(Player*, Location);
        void sendUpdateToPlayers(SocketMessage);
        SocketMessage visitorMove(Player*, Location, Location);
        SocketMessage hypotheque(Player*, Location);
        SocketMessage buyBack(Player*, Location);
        SocketMessage roadBlock(Player*, Location);
        //SocketMessage getRealTimeRem(Player*);
        //SocketMessage getTimeRem(Player*);
		std::vector<Location> giveWay();
        //Spawnable getRandomSpawn();
};

#endif

