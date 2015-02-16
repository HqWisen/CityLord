#ifndef CITYLORDMANAGER_HPP_
#define CITYLORDMANAGER_HPP_

#include <iostream>
#include <string>

// A être inclus dans le fichier du serveur

#include "../common/lib/Building.hpp"
#include "../common/lib/BuildingType.hpp"
#include "../common/lib/Case.hpp"
#include "../common/lib/Catalog.hpp"
#include "../common/lib/City.hpp"
#include "../common/lib/common.h"
//#include "../common/lib/Field.hpp"
#include "../common/lib/Map.hpp"
//#include "../common/lib/Neighborhood.hpp"
#include "../common/lib/Obstacle.hpp"
#include "../common/lib/Player.hpp"
#include "../common/lib/Road.hpp"
#include "../common/lib/User.hpp"
#include "../common/template/SocketMessage.hpp"

class CityLordManager{
	Map _cityMap; 
    Catalog _catalog;

public:
    CityLordManager(Map);
    SocketMessage makePurchase(Player&, int, int); //Implique que les coordonnées de la case sont envoyées du client vers le serveur et ont été décodées
    SocketMessage makeTrade(Player&, Player&, int , int, int);
    SocketMessage buildBuilding(Player&, int, int, std::string);
    SocketMessage destroyBuilding(Player&, int, int);
    SocketMessage upgradeBuilding(Player&, int, int);
    std::string showCatalog();
    std::string showCity();
}

#endif

