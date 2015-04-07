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


void UpdateSystem::refresh(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
    Location location = Location::parse(update.get("location"));
    //client->repaintView();
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

void UpdateSystem::createvisitor(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	int id = atoi(update.get("visitorid").c_str());
    Location spawnLocation = Location::parse(update.get("spawnlocation"));
    client->createVisitor(id, spawnLocation);
    pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::movevisitor(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	int id = atoi(update.get("visitorid").c_str());
    Location firstLocation = Location::parse(update.get("firstlocation"));
    Location lastLocation = Location::parse(update.get("lastlocation"));
    client->moveVisitor(id, lastLocation);
    pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::removevisitor(ClientManager* client, SocketMessage update){
    pthread_mutex_lock(&updatemutex);
	int id = atoi(update.get("visitorid").c_str());
    client->removeVisitor(id);
    pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::offer(ClientManager* client, SocketMessage update){
	pthread_mutex_lock(&updatemutex);
	Location location = Location::parse(update.get("location"));
	int price = std::stoi(update.get("offerprice"));
	ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
	field->setOfferedPrice(price);
	pthread_mutex_unlock(&updatemutex);
}

void UpdateSystem::offercancel(ClientManager* client, SocketMessage update){
	pthread_mutex_lock(&updatemutex);
	Location location = Location::parse(update.get("location"));
	ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
	field->setOfferedPrice(0);
	pthread_mutex_unlock(&updatemutex);
}

