#include "CityManager.hpp"
#include "UserManager.hpp"

const int CityManager::DEFAULTMAXPLAYER = 3;

CityManager::CityManager(std::string mn, int cityid, User* cr) : mapname(mn), cityMap(new Map<Field>(getMapFileName())), id(cityid), creator(cr), catalog(), nPlayer(0), playerVector(), MAXPLAYER(DEFAULTMAXPLAYER){
    Field* concernedField;
    for(int row = 0; row<cityMap->getNumberOfRows(); row++){
        for(int col = 0; col<cityMap->getNumberOfCols(); col++){
            Location currentLocation = Location (row, col);
            if((concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation)))){
                catalog.putOnMarket(concernedField);
			}
		}
	}
<<<<<<< HEAD
    updater = new CityUpdater(getMap(), playerVector);
=======
    //updater = new CityUpdater(getMap());
>>>>>>> a3a0b7559a241a48a694d8286e93d1e47e569220
}

CityManager::~CityManager(){
    delete updater;
    delete cityMap;
}

std::string CityManager::getMapFileName(){
    return MAPFILEPATH + mapname + ".txt";
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

int CityManager::getMaxPlayer(){
    return MAXPLAYER;
}

int CityManager::getNextID(){
    return getNPlayer();
}

std::string CityManager::getName(){
    return "City NID["+std::to_string(id)+"]";
}

bool CityManager::canJoin(Player* player){
    return alreadyInCity(player) || nPlayer < MAXPLAYER;
}

void CityManager::addPlayer(Player* player){
    if(!alreadyInCity(player)){
        playerVector.push_back(player);
        nPlayer++;
    }
}

bool CityManager::alreadyInCity(Player* player){
    return std::find(playerVector.begin(), playerVector.end(), player) != playerVector.end();

}

Map<Field>* CityManager::getMap(){
    return cityMap;
}

/*
std::vector<Player*>* CityManager::getPlayerVector(){
	return playerVector;
}
*/

User* CityManager::getCreator(){
    return creator;
}

std::vector<Field*> CityManager::getPurchasableFields(){
	return catalog.getPurchasableFields();
}

//-------------------------------

SocketMessage CityManager::visitorMove(Player* player, Location firstLocation, Location lastLocation){
	SocketMessage update;
	update.setTopic("visitormove");
	update.set("firstlocation", firstLocation.toString());
	update.set("lastlocation", lastLocation.toString());

	return update;

}

//------------------------------


SocketMessage CityManager::makePurchase(Player* player, Location location){
	//Regarde si le joueur 1 a assez d'argent
	// Si oui, le cataloque est mis a jour, le joueur obtient la parcelle et un message est envoyé
	// Si non, un message est envoyé
    SocketMessage message, update;
    Field* concernedField;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
        if(catalog.isOnMarket(concernedField)){
			if(concernedField->hasBuilding()){
				if(player->getMoney() >= concernedField->getPrice() + concernedField->getBuilding()->getPrice()){
					player->setMoney(player->getMoney() - (concernedField->getPrice() + concernedField->getBuilding()->getPrice()));
					catalog.give(concernedField, player);
                    update.setTopic("changeownerwithbuilding");
                    update.set("ownerid", std::to_string(player->getPlayerID()));
                    update.set("typeindex", std::to_string(BuildingType::getIndexByType(concernedField->getBuilding()->getType())));
                    update.set("level", std::to_string(concernedField->getBuilding()->getLevel()));
                    update.set("location", location.toString());
                    updater->sendUpdateToPlayers(update);
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
                    update.setTopic("changeowner");
                    update.set("ownerid", std::to_string(player->getPlayerID()));
                    update.set("location", location.toString());
                    sendUpdateToPlayers(update);
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



SocketMessage CityManager::buildBuilding(Player* player, Location location, BuildingType buildingType){
    SocketMessage message, update;
    Field* concernedField;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
        if(concernedField->getOwner() == player){
			if(!concernedField->hasBuilding()){
				if(player->getMoney() >= buildingType.price){
					player->setMoney(player->getMoney() - buildingType.price);
					player->buildBuilding();
					concernedField->buildBuilding(buildingType);
                    update.setTopic("build");
                    update.set("location", location.toString());
                    update.set("typeindex", std::to_string(BuildingType::getIndexByType(buildingType)));
                    update.set("level", std::to_string(concernedField->getBuilding()->getLevel()));
                    updater->sendUpdateToPlayers(update);
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

SocketMessage CityManager::upgradeBuilding(Player* player, Location location){

	SocketMessage message;
    Field* concernedField;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
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

SocketMessage CityManager::destroyBuilding(Player* player, Location location){
    SocketMessage message, update;
    Field* concernedField;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
        if(concernedField->getOwner() == player){
			if(concernedField->hasBuilding()){
				if(player->getMoney() >= concernedField->getBuilding()->getDestructionCost()){
					player->setMoney(player->getMoney() - concernedField->getBuilding()->getDestructionCost());
					player->destroyBuilding();
					concernedField->destroyBuilding();
                    update.setTopic("destroy");
                    update.set("location", location.toString());
                    updater->sendUpdateToPlayers(update);
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



/*Spawnable CityManager::getRandomSpawn(){
    int size = listSpawnable.size();
    int luck = rand() %  (size-1);
    return listSpawnable[luck];
}*/


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

*/
