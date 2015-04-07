#include "CityManager.hpp"
#include "UserManager.hpp"

const int CityManager::DEFAULTMAXPLAYER = 8;

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
    updater = new CityUpdater(getMap(), &playerVector);
    updater->start();
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

std::string CityManager::getStringTimer(){
    return updater->getStringTimer();
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

/*void CityManager::sendVisitorsFor(UserManager* userManager){
    pthread_mutex_lock(&updater->visitormutex);
    std::cout<<"building visitor for "<<userManager->getUserName()<<std::endl;
    pthread_mutex_unlock(&updater->visitormutex);
}*/

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


std::vector<Offer*> CityManager::getOffers(){
	return catalog.getOffers();
}

//-------------------------------

SocketMessage CityManager::visitorMove(Player* player, Location firstLocation, Location lastLocation){
	SocketMessage update;
	update.setTopic("visitormove");
	update.set("firstlocation", firstLocation.toString());
	update.set("lastlocation", lastLocation.toString());

	return update;

}

/*
SocketMessage CityManager::getTimeRem(Player* player){
    SocketMessage timeRem;

	int x = updater->getTimeRemaining();
	int hour = x/3600 ;
	int min = x/60;
	int sec = x-(hour*3600)-(min*60);
	//timeRem.setTopic("gettimeremaining");
	timeRem.set("hour", std::to_string(hour));
	timeRem.set("min", std::to_string(min));
	timeRem.set("sec", std::to_string(sec));

    return timeRem;
}

SocketMessage CityManager::getRealTimeRem(Player* player){
	SocketMessage realTimeRem;

    int x = updater->getRealTimeRemaining();
	int hour = x/3600 ;
	int min = x/60;
	int sec = x-(hour*3600)-(min*60);
	//realTimeRem.setTopic("gettimeremaining");
	realTimeRem.set("hour", std::to_string(hour));
	realTimeRem.set("min", std::to_string(min));
    realTimeRem.set("sec", std::to_string(sec));

	return realTimeRem;
}
*/

//------------------------------

SocketMessage CityManager::makePurchase(Player* player, Location location){
	//Regarde si le joueur 1 a assez d'argent
	// Si oui, le cataloque est mis a jour, le joueur obtient la parcelle et un message est envoyé
	// Si non, un message est envoyé
    SocketMessage message, update;
    Field* concernedField;
    int price;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
        if(catalog.isOnMarket(concernedField)){
			if(concernedField->getOwner() == nullptr){
				price = concernedField->getTotalPurchasePrice();
			}else{
				price = concernedField->getOfferedPrice();
			}
            if(player->getMoney() >= price){
				if(concernedField->getOwner() != nullptr){
					Player* offeringPlayer = concernedField->getOwner();
					offeringPlayer->gainMoney(price);
					offeringPlayer->removeField(concernedField);
					if(concernedField->hasBuilding()){
						offeringPlayer->decBuildingCounter();
					}
					concernedField->setOfferedPrice(0);
				}	
                player->loseMoney(price);
                catalog.give(concernedField, player);
                if(concernedField->hasBuilding()){
					player->incBuildingCounter();
				}
                update.setTopic("changeowner");
                update.set("ownerid", std::to_string(player->getPlayerID()));
                update.set("location", location.toString());
                updater->sendUpdateToPlayers(update);
                message.setTopic("success");
                message.set("reason", "Field has been successfully purchased !");
            }else{
                message.setTopic("failure");
                message.set("reason", "You do not own enough money !");
            }
        }else{
			message.setTopic("failure");
            message.set("reason", "Field is not on the catalog !");
		}
	}else{
		message.setTopic("failure");
        message.set("reason", "This is not a field !");
	}
	return message;
}



SocketMessage CityManager::buildBuilding(Player* player, Location location, BuildingType buildingType){
    SocketMessage message, update;
    Field* concernedField;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
        if(concernedField->getOwner() == player){
			if(!concernedField->hasBuilding()){
                if(player->getMoney() >= buildingType.getTotalPurchasePrice()){
                    player->loseMoney(buildingType.getTotalPurchasePrice());
                    player->incBuildingCounter();
					concernedField->buildBuilding(buildingType);
					updater->refreshBuildingsList();
                    update.setTopic("build");
                    update.set("location", location.toString());
                    update.set("typeindex", std::to_string(BuildingType::getIndexByType(buildingType)));
                    update.set("level", std::to_string(concernedField->getBuilding()->getLevel()));
                    updater->sendUpdateToPlayers(update);
                    message.setTopic("success");
                    message.set("reason", "Building has been successfully built !");
				}else{
					message.setTopic("failure");
                    message.set("reason", "You do not have enough money !");
				}
			}else{
				message.setTopic("failure");
                message.set("reason", "This Field already has a building !");
			}
		}else{
			message.setTopic("failure");
            message.set("reason", "You do not own this Field !");
		}
	}else{
		message.setTopic("failure");
        message.set("reason", "This is not a Field !");
	}
		return message;
}

SocketMessage CityManager::upgradeBuilding(Player* player, Location location){
	SocketMessage message;
    Field* concernedField;
    if((concernedField = dynamic_cast<Field*>(cityMap->getCase(location)))){;
        if(concernedField->getOwner() == player){
			if(concernedField->hasBuilding()){
                if(player->getMoney() >= concernedField->getBuilding()->getType().UPGRADECOST){
                    player->loseMoney(concernedField->getBuilding()->getType().UPGRADECOST);
					concernedField->getBuilding()->upgrade();
					message.setTopic("success");
                    message.set("reason", "Building has been successfully upgraded !");
				}else{
					message.setTopic("failure");
                    message.set("reason", "You do not have enough money !");
				}
			}else{
				message.setTopic("failure");
                message.set("reason", "This Field has no building !");
			}
		}else{
			message.setTopic("failure");
            message.set("reason", "You do not own this Field !");
		}
	}else{
		message.setTopic("failure");
        message.set("reason", "This is not a Field !");
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
                    player->loseMoney(concernedField->getBuilding()->getDestructionCost());
                    player->decBuildingCounter();
					concernedField->destroyBuilding();
					updater->refreshBuildingsList();
                    update.setTopic("destroy");
                    update.set("location", location.toString());
                    updater->sendUpdateToPlayers(update);
					message.setTopic("success");
                    message.set("reason", "Building has been successfully destroyed !");
				}else{
					message.setTopic("failure");
                    message.set("reason", "You do not have enough money !");
				}
			}else{
				message.setTopic("failure");
                message.set("reason", "This Field has no building !");
			}
		}else{
			message.setTopic("failure");
            message.set("reason", "You do not own this Field !");
		}
	}else{
		message.setTopic("failure");
        message.set("reason", "This is not a Field !");
	}
	return message;
}



/*Spawnable CityManager::getRandomSpawn(){
    int size = listSpawnable.size();
    int luck = rand() %  (size-1);
    return listSpawnable[luck];
}*/



SocketMessage CityManager::offer(Player* player, Location location, int price){
	SocketMessage message, update;
	Field* concernedField;
	if((dynamic_cast<Field*>(cityMap->getCase(location)))){
		concernedField = dynamic_cast<Field*>(cityMap->getCase(location));
		if(concernedField->getOwner() == player){
			if(concernedField->getOfferedPrice() == 0){
				concernedField->setOfferedPrice(price);
				catalog.putOnMarket(concernedField);
				update.setTopic("offer");
				update.set("location", location.toString());
				update.set("offerprice", std::to_string(price));
				updater->sendUpdateToPlayers(update);
				message.setTopic("success");
                message.set("reason", "Offer has been successfully registered !");
			}else{
				message.setTopic("failure");
                message.set("reason", "This Field has already been offered !");
			}
		}else{
			message.setTopic("failure");
            message.set("reason", "You do not own this Field !");
		}
	}else{
		message.setTopic("failure");
        message.set("reason", "This is not a Field !");
	}
	return message;
}


SocketMessage CityManager::cancelOffer(Player* player, Location location){
	SocketMessage message, update;
	Field* concernedField;
	if((dynamic_cast<Field*>(cityMap->getCase(location)))){;
		concernedField = dynamic_cast<Field*>(cityMap->getCase(location));
		if(concernedField->getOwner() == player){
			if(concernedField->getOfferedPrice() != 0){
				concernedField->setOfferedPrice(0);
				catalog.removeFromMarket(concernedField);
				update.setTopic("offercancel");
				update.set("location", location.toString());
				updater->sendUpdateToPlayers(update);
				message.setTopic("success");
				message.set("reason", "Offer has been successfully removed!");
			}else{
				message.setTopic("success");
				message.set("reason", "You have not offered this Field!");
			}
		}else{
			message.setTopic("failure");
			message.set("reason", "You do not own this Field!");
		}
	}else{
		message.setTopic("failure");
		message.set("reason", "This is not a Field");
	}
	return message;
}
			

