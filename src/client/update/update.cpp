#include "update.hpp"

namespace update{
    void changeowner(CityLordClient* client, SocketMessage update){
        Location location = Location::parse(update.get("location"));
        int ownerid = std::stoi(update.get("ownerid"));
        ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
        field->setOwnerID(ownerid);
    }
    void changeownerwithbuilding(CityLordClient* client, SocketMessage update){
        Location location = Location::parse(update.get("location"));
        int ownerid = std::stoi(update.get("ownerid"));
        int level = std::stoi(update.get("level"));
        BuildingType type = BuildingType::getTypeByIndex(std::stoi(update.get("typeindex")));
        ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
        field->setOwnerID(ownerid);
        field->buildBuilding(type, level);
    }
    void build(CityLordClient* client, SocketMessage update){
        Location location = Location::parse(update.get("location"));
        int level = std::stoi(update.get("level"));
        BuildingType type = BuildingType::getTypeByIndex(std::stoi(update.get("typeindex")));
        ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
        field->buildBuilding(type, level);
    }
    void destroy(CityLordClient* client, SocketMessage update){
        Location location = Location::parse(update.get("location"));
        ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
        field->destroyBuilding();
    }

}


