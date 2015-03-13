#include "update.hpp"


void UpdateMethods::changeowner(ClientManager* client, SocketMessage update){
    Location location = Location::parse(update.get("location"));
    int ownerid = std::stoi(update.get("ownerid"));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->setOwnerID(ownerid);
    client->repaint();
}
void UpdateMethods::changeownerwithbuilding(ClientManager* client, SocketMessage update){
    Location location = Location::parse(update.get("location"));
    int ownerid = std::stoi(update.get("ownerid"));
    int level = std::stoi(update.get("level"));
    BuildingType type = BuildingType::getTypeByIndex(std::stoi(update.get("typeindex")));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->setOwnerID(ownerid);
    field->buildBuilding(type, level);
    client->repaint();
}
void UpdateMethods::build(ClientManager* client, SocketMessage update){
    Location location = Location::parse(update.get("location"));
    int level = std::stoi(update.get("level"));
    BuildingType type = BuildingType::getTypeByIndex(std::stoi(update.get("typeindex")));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->buildBuilding(type, level);
    client->repaint();
}
void UpdateMethods::destroy(ClientManager* client, SocketMessage update){
    Location location = Location::parse(update.get("location"));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->destroyBuilding();
    client->repaint();
}

void UpdateMethods::visitormove(ClientManager* client, SocketMessage update){
    Location firstLocation = Location::parse(update.get("firstLocation"));
    Location lastLocation = Location::parse(update.get("lastLocation"));
    //Visitor.moveGui ??
}




