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
    updater = new CityUpdater(getMap());
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

User* CityManager::getCreator(){
    return creator;
}

std::vector<Field*> CityManager::getPurchasableFields(){
	return catalog.getPurchasableFields();
}

std::vector<Offer*> CityManager::getOffers(){
	return catalog.getOffers();
}

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
                    sendUpdateToPlayers(update);
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
                    sendUpdateToPlayers(update);
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
                    sendUpdateToPlayers(update);
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

void CityManager::sendUpdateToPlayers(SocketMessage update){
    Player* player;
    for (std::vector<Player*>::iterator it = playerVector.begin(); it != playerVector.end(); it++){
        player = *it;
        if(player->isConnected()){
            player->getUserManager()->sendUpdate(update);
        }

    }
}

/*Spawnable CityManager::getRandomSpawn(){
    int size = listSpawnable.size();
    int luck = rand() %  (size-1);
    return listSpawnable[luck];
}*/



SocketMessage CityManager::makeTrade(Player* offeringPlayer, Player* purchasingPlayer, Location location){
	//Regarde si le joueur 1 a assez d'argent
	//	Si oui, l'échange est effectué et des messages sont envoyés
	//	Si non, un message est envoyé au joueur 1
	SocketMessage message = SocketMessage();
	Field* concernedField;
	int offerIndex;
	if((dynamic_cast<Field*>(cityMap->getCase(location)))){;
		concernedField = dynamic_cast<Field*>(cityMap->getCase(location));
		if(concernedField->getOwner() == offeringPlayer){
			offerIndex = catalog.isOfferOnMarket(concernedField);
			if(offerIndex != -1){
				int price = (catalog.getOffers())[offerIndex]->getPrice();
				if(purchasingPlayer->getMoney() >= price){
					offeringPlayer->setMoney(offeringPlayer->getMoney() + price);
					purchasingPlayer->setMoney(purchasingPlayer->getMoney() - price);
					concernedField->setOwner(purchasingPlayer);
					catalog.removeOffer(offerIndex);
					message.setTopic("success");
					message.set("reason", "Trade has been successful!");
				}else{
					message.setTopic("failure");
					message.set("reason", "The purchasing player does not have enough money!");
				}
			}else{
				message.setTopic("failure");
				message.set("reason", "This Field has not been offered!");
			}
		}else{
			message.setTopic("failure");
			message.set("reason", "The offering player does not have this Field!");
		}
	}else{
		message.setTopic("failure");
		message.set("reason", "This is not a Field!");
	}
	return message;
}

/*
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
