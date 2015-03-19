#include "update.hpp"

pthread_mutex_t UpdateSystem::updatemutex(PTHREAD_MUTEX_INITIALIZER);

void UpdateSystem::changeowner(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
		Location location = Location::parse(update.get("location"));
    int ownerid = std::stoi(update.get("ownerid"));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->setOwnerID(ownerid);
    client->repaint();
		pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::build(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
		Location location = Location::parse(update.get("location"));
    int level = std::stoi(update.get("level"));
    BuildingType type = BuildingType::getTypeByIndex(std::stoi(update.get("typeindex")));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->buildBuilding(type, level);
    client->repaint();
    pthread_mutex_unlock(&updatemutex);
}
void UpdateSystem::destroy(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	Location location = Location::parse(update.get("location"));
    ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
    field->destroyBuilding();
    client->repaint();
	pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::updatemoney(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
    client->updateMoney(std::stoi(update.get("money")));
    pthread_mutex_unlock(&updatemutex);
}
void UpdateSystem::updatetime(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
    client->updateTime(update.get("time"));
    pthread_mutex_unlock(&updatemutex);
}
void UpdateSystem::createvisitor(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	int id = atoi(update.get("visitorid").c_str());
    Location spawnLocation = Location::parse(update.get("spawnlocation"));
    //client->getMap()->addVisitor(id, spawnLocation);
    //std::cout<<"Visitor "<<id<<" added"<<std::endl;
	pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::movevisitor(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	int id = atoi(update.get("visitorid").c_str());
    Location firstLocation = Location::parse(update.get("firstlocation"));
    Location lastLocation = Location::parse(update.get("lastlocation"));
    //client->getMap()->getVisitor(id)->getLoc().setRow(lastLocation.getRow());
    //client->getMap()->getVisitor(id)->getLoc().setCol(lastLocation.getCol());
    //std::cout<<"Visitor "<<id<<" moved"<<std::endl;
    //Visitor.moveGui ??
	pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::removevisitor(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	int id = atoi(update.get("visitorid").c_str());
    client->getMap()->deleteVisitor(id);
    // std::cout<<"Visitor "<<id<<" removed"<<std::endl;
    pthread_mutex_unlock(&updatemutex);
}



