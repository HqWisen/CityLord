#include "CityManager.hpp"


CityManager::CityManager(std::string mapname_, int id_) : mapname(mapname_), cityMap(mapname_), id(id_), catalog(), nPlayer(0){
	for(int x = 0; x<cityMap.getDimensionX(); x++){
		for(int y = 0; y<cityMap.getDimensionY(); y++){
			Location currentLocation = Location (x,y);
			if(cityMap.getCase(currentLocation)->getType() == "Field"){
				Field* concernedField = dynamic_cast<Field*>(cityMap.getCase(currentLocation));
				catalog.putOnMarket(concernedField);
			}
		}
	}
	new Generator();
}

std::string CityManager::getMapName(){
	return mapname;
}

int CityManager::getID(){
	return id;
}

int CityManager::getNPlayer(){
	return nPlayer;
}

void CityManager::addPlayer(Player* player){
	//playerVector.push_back(player);
	nPlayer++;
}

Map* CityManager::getMap(){
	return &cityMap;
}

std::vector<Field*> CityManager::getPurchasableFields(){
	return catalog.getPurchasableFields();
}


SocketMessage CityManager::makePurchase(Player* player, Location coordinates){
	//Regarde si le joueur 1 a assez d'argent
	// Si oui, le cataloque est mis a jour, le joueur obtient la parcelle et un message est envoyé
	// Si non, un message est envoyé
	SocketMessage message;
	if(cityMap.getCase(coordinates)->getType() == "Field"){;
		Field* concernedField = dynamic_cast<Field*>(cityMap.getCase(coordinates));
		if(catalog.isOnMarket(concernedField)){
			if(concernedField->hasBuilding()){
				if(player->getMoney() >= concernedField->getPrice() + concernedField->getBuilding()->getPrice()){
					player->setMoney(player->getMoney() - (concernedField->getPrice() + concernedField->getBuilding()->getPrice()));
					catalog.give(concernedField, player);
					message.setTopic("success");
					message.set("reason", "Field has been successfully purchased!");
				}else{
					message.setTopic("failure");
					message.set("reason", "You do not own enough money!");
				}
			}else{
				if(player->getMoney() >= concernedField->getPrice()){
					player->setMoney(player->getMoney() - concernedField->getPrice());
					catalog.give(concernedField, player);
					message.setTopic("success");
					message.set("reason", "Field has been successfully purchased!");
				}else{
					message.setTopic("failure");
					message.set("reason", "You do not own enough money!");
				}
			}
		}else{
			message.setTopic("failure");
			message.set("reason", "Field is not on the catalog, therefore it was purchased by someone else");
		}
	}else{
		message.setTopic("failure");
		message.set("reason", "This is not a Field!");
	}
	return message;
}



SocketMessage CityManager::buildBuilding(Player* player, Location coordinates, BuildingType buildingType){
	SocketMessage message;
	if(cityMap.getCase(coordinates)->getType() == "Field"){;
		Field *concernedField = dynamic_cast<Field*>(cityMap.getCase(coordinates));
		if(concernedField->getOwner() == player){
			if(!concernedField->hasBuilding()){
				if(player->getMoney() >= buildingType.price){
					player->setMoney(player->getMoney() - buildingType.price);
					player->buildBuilding();
					concernedField->buildBuilding(buildingType);
					message.setTopic("success");
					message.set("reason", "Building has been successfully built!");
				}else{
					message.setTopic("failure");
					message.set("reason", "You do not have enough money!");
				}
			}else{
				message.setTopic("failure");
				message.set("reason", "This Field already has a building!");
			}
		}else{
			message.setTopic("failure");
			message.set("reason", "You do not own this Field!");
		}
	}else{
		message.setTopic("failure");
		message.set("reason", "This is not a Field!");
	}
		return message;
}

SocketMessage CityManager::upgradeBuilding(Player* player, Location coordinates){

	SocketMessage message;
	if(cityMap.getCase(coordinates)->getType() == "Field"){;
		Field *concernedField = dynamic_cast<Field*>(cityMap.getCase(coordinates));
		if(concernedField->getOwner() == player){
			if(concernedField->hasBuilding()){
				if(player->getMoney() >= concernedField->getBuilding()->getType().upgradeCost){
					player->setMoney(player->getMoney() - concernedField->getBuilding()->getType().upgradeCost);
					concernedField->getBuilding()->upgrade();
					message.setTopic("success");
					message.set("reason", "Building has been successfully upgraded!");
				}else{
					message.setTopic("failure");
					message.set("reason", "You do not have enough money!");
				}
			}else{
				message.setTopic("failure");
				message.set("reason", "This Field has no building!");
			}
		}else{
			message.setTopic("failure");
			message.set("reason", "You do not own this Field!");
		}
	}else{
		message.setTopic("failure");
		message.set("reason", "This is not a Field!");
	}
	return message;
}

SocketMessage CityManager::destroyBuilding(Player* player, Location coordinates){
	SocketMessage message;
	if(cityMap.getCase(coordinates)->getType() == "Field"){;
		Field* concernedField = dynamic_cast<Field*>(cityMap.getCase(coordinates));
		if(concernedField->getOwner() == player){
			if(concernedField->hasBuilding()){
				if(player->getMoney() >= concernedField->getBuilding()->getDestructionCost()){
					player->setMoney(player->getMoney() - concernedField->getBuilding()->getDestructionCost());
					player->destroyBuilding();
					concernedField->destroyBuilding();
					message.setTopic("success");
					message.set("reason", "Building has been successfully destroyed!");
				}else{
					message.setTopic("failure");
					message.set("reason", "You do not have enough money!");
				}
			}else{
				message.setTopic("failure");
				message.set("reason", "This Field has no building!");
			}
		}else{
			message.setTopic("failure");
			message.set("reason", "You do not own this Field!");
		}
	}else{
		message.setTopic("failure");
		message.set("reason", "This is not a Field!");
	}
	return message;
}

Spawnable CityManager::getRandomSpawn(){
    int size = listSpawnable.size();
    int luck = rand() %  (size-1);
    return listSpawnable[luck];
}


/*
SocketMessage CityLordManager::makeTrade(Player& player1, Player& player2, Location coordinates, int offeredMoney){
	//Regarde si le joueur 1 a assez d'argent
	//	Si oui, l'échange est effectué et des messages sont envoyés
	//	Si non, un message est envoyé au joueur 1
	SocketMessage message = SocketMessage();
	if(cityMap.getCase(coordinates).getType() == "Field"){;
		Field *concernedField = cityMap.getCase(coordinates);
		if(*concernedField.getOwner() == player2.number){
			if(player1.getMoney() >= offeredMoney){
				player1.setMoney(player1.getMoney() - offeredMoney);
				player2.setMoney(player2.getMoney() + offeredMoney);
				*concernedField.setOwner(player1);
				message.setTopic(TOPIC_SUCCESS);
				message.set("reason", "Trade has been successful!");
			}else{
				message.setTopic(TOPIC_FAILURE);
				message.set("reason", "The purchasing player does not have enough money!");
			}
		}else{
			message.setTopic(TOPIC_FAILURE);
			message.set("reason", "The offering player does not have this case!");
		}
	}else{
		message.setTopic(TOPIC_FAILURE);
		message.set("reason", "This is not a Field!");
	}
	return message;*
}


std::string showCatalog(){
	//Envoie le statut du catalogue de la ville
	std::string message = ""
	for(int i = 0; i<_catalog.getBuyable().size(); i++){
		message = message + (_catalog.getBuyable()[i])->display() + "\n" + "-----------" + "\n";
	}
	return message;
}

std::string showCity(){
	//Envoie la carte de la ville gérée par ce manager
	return cityMap.display();
}

void updateBuildings(){
	//Mets à jour tous les buildings dans cityMap en introduisant des visiteurs
	srand( time(NULL) );
	Visitor randomVisitor:
	for(int coordX = 0; coordX<=dimensionX; coordX++){
		for(int coordY = 0; coordY<=dimensionY; coordY++){
			if(cityMap.getCase(coordinates).getType() == "Field"){
				Field *concernedField = cityMap.getCase(coordinates);
				if(*concernedField.hasBuilding()){
					*concernedField.getBuilding().visitorList.clear();
					int numberOfVisitors = rand % 10;
					for(int visitors = 0; visitors < numberOfVisitors; visitors++){
						randomVisitor = Visitor();
						*concernedField.getBuilding().receiveVisitor(randomVisitor);
					}
				}
			}
		}
	}
}
						
*/
