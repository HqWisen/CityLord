#include "update.hpp"

void UpdateMethods::changeowner(ClientManager* client, SocketMessage update){
    Location location = Location::parse(update.get("location"));
    int ownerid = std::stoi(update.get("ownerid"));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->setOwnerID(ownerid);
    client->repaint();
}
/*void UpdateMethods::changeownerwithbuilding(ClientManager* client, SocketMessage update){
    Location location = Location::parse(update.get("location"));
    int ownerid = std::stoi(update.get("ownerid"));
    int level = std::stoi(update.get("level"));
    BuildingType type = BuildingType::getTypeByIndex(std::stoi(update.get("typeindex")));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->setOwnerID(ownerid);
    field->buildBuilding(type, level);
    client->repaint();
}*/
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

void UpdateMethods::visitorcreate(ClientManager* client, SocketMessage update){
    int id = atoi(update.get("visitorid").c_str());
    Location spawnLocation = Location::parse(update.get("spawnlocation"));
    //client->getMap()->addVisitor(id, spawnLocation);
    //std::cout<<"Visitor "<<id<<" added"<<std::endl;
}

void UpdateMethods::visitormove(ClientManager* client, SocketMessage update){
    int id = atoi(update.get("visitorid").c_str());
    Location firstLocation = Location::parse(update.get("firstlocation"));
    Location lastLocation = Location::parse(update.get("lastlocation"));
    //client->getMap()->getVisitor(id)->getLoc().setRow(lastLocation.getRow());
    //client->getMap()->getVisitor(id)->getLoc().setCol(lastLocation.getCol());
    //std::cout<<"Visitor "<<id<<" moved"<<std::endl;
    //Visitor.moveGui ??
}

void UpdateMethods::visitorremove(ClientManager* client, SocketMessage update){
    int id = atoi(update.get("visitorid").c_str());
    client->getMap()->deleteVisitor(id);
   // std::cout<<"Visitor "<<id<<" removed"<<std::endl;
}



