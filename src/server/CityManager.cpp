#include "CityManager.hpp"


CityManager::CityManager(std::string mapname_, int number_) : mapname(mapname_), cityMap(mapname_), number(number_){
	//_catalog = Catalog();
}

std::string CityManager::getMapName(){
	return mapname;
}

int CityManager::getNumber(){
	return number;
}

Map& CityManager::getMap(){
	return cityMap;
}

/*
SocketMessage CityLordManager::buildBuilding(Player& player, int coordX, int coordY, BuildingType buildingType){
	//Regarde si le joueur est le propriétaire de la parcelle:
	//	Si oui, regarde si la parcelle est vide
	//		Si oui, regarde si le joueur a assez d'argent
	//			Si oui, le building est créé et un message est envoyé
	//			Si non, un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
	SocketMessage message = SocketMessage();
	if(_cityMap.getCase(coordX, coordY).getType() == "FIELD"){;
		Field *concernedField = _cityMap.getCase(coordX, coordY);
		if(*concernedField.getOwner() == player.number){
			if(!concernedCase.hasBuilding()){
				if(player.getMoney() >= buildingType.getPrice()){
					player.setMoney(player.getMoney() - buildingType.getPrice());
					Building building = Building(buildingType, player);
					*concernedField.setBuilding(building);
					message.setTopic(TOPIC_SUCCESS);
					message.set("reason", "Building has been successfully built!")
				}else{
					message.setTopic(TOPIC_FAILURE);
					message.set("reason", "You do not have enough money!")
				}
			}else{
				message.set(TOPIC_FAILURE);
				message.set("reason", "This field already has a building!");
			}
		}else{
			message.setTopic(TOPIC_FAILURE);
			message.set("reason", "You do not own this field!");
		}
	}else{
		message.setTopic(TOPIC_FAILURE);
		message.set("reason", "This is not a field!");
	}
		return message;
}

SocketMessage CityLordManager::upgradeBuilding(Player& player, int coordX, int coordY){
	//Regarde si le joueur est le propriétaire de la parcelle et qu'elle contient un bulding:
	//	Si oui, regarde si le building peut être amélioré
	//		Si oui, regarde si le joueur a assez d'argent
	//			Si oui, le building est amélioré et un message est envoyé
	//			Si non, un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
	SocketMessage message = SocketMessage();
	if(_cityMap.getCase(coordX, coordY).getType() == "FIELD"){;
		Field *concernedField = _cityMap.getCase(coordX, coordY);
		if(*concernedField.getOwner() == player.number){
			if(*concernedField.hasBuilding()){
				if(player.getMoney() >= *concernedField.getBuilding().type.upgradeCost){
					player.setMoney(player.getMoney() - *concernedField.getBuilding().type.upgradeCost);
					*concernedField.getBuilding().upgrade();
					message.setTopic(TOPIC_SUCCESS);
					message.set("reason", "Building has been successfully upgraded!")
				}else{
					message.setTopic(TOPIC_FAILURE);
					message.set("reason", "You do not have enough money!")
				}
			}else{
				message.set(TOPIC_FAILURE);
				message.set("reason", "This field has no building!");
			}
		}else{
			message.setTopic(TOPIC_FAILURE);
			message.set("reason", "You do not own this field!");
		}
	}else{
		message.setTopic(TOPIC_FAILURE);
		message.set("reason", "This is not a field!");
	}
	return message;
}

SocketMessage CityLordManager::destroyBuilding(Player& player, int coordX, int coordY){
	//Regarde si le joueur est le propriétaire de la parcelle et qu'elle contient un bulding:
	//	Si oui, regarde si le joueur a assez d'argent
	//		Si oui, le building est amélioré et un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
	SocketMessage message = SocketMessage();
	if(_cityMap.getCase(coordX, coordY).getType() == "FIELD"){;
		Field *concernedField = _cityMap.getCase(coordX, coordY);
		if(concernedCase.getOwner() == player.number){
			if(*concernedField.hasBuilding()){
				if(player.getMoney() >= *concernedField.getBuilding().destructionCost){
					player.setMoney(player.getMoney() - *concernedField.getBuilding().destructionCost);
					*concernedField.destroyBuilding();
					message.setTopic(TOPIC_SUCCESS);
					message.set("reason", "Building has been successfully destroyed!")
				}else{
					message.setTopic(TOPIC_FAILURE);
					message.set("reason", "You do not have enough money!")
				}
			}else{
				message.set(TOPIC_FAILURE);
				message.set("reason", "This field has no building!");
			}
		}else{
			message.setTopic(TOPIC_FAILURE);
			message.set("reason", "You do not own this field!");
		}
	}else{
		message.setTopic(TOPIC_FAILURE);
		message.set("reason", "This is not a field!");
	}
	return message;
}

SocketMessage CityLordManager::makeTrade(Player& player1, Player& player2, int coordX, int coordY, int offeredMoney){
	//Regarde si le joueur 1 a assez d'argent
	//	Si oui, l'échange est effectué et des messages sont envoyés
	//	Si non, un message est envoyé au joueur 1
	SocketMessage message = SocketMessage();
	if(_cityMap.getCase(coordX, coordY).getType() == "FIELD"){;
		Field *concernedField = _cityMap.getCase(coordX, coordY);
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
		message.set("reason", "This is not a field!");
	}
	return message;*
}

SocketMessage CityLordManager::makePurchase(Player& player, int coordX, int coordY){
	//Regarde si le joueur 1 a assez d'argent
	// Si oui, le cataloque est mis a jour, le joueur obtient la parcelle et un message est envoyé
	// Si non, un message est envoyé
	SocketMessage message = SocketMessage();
	if(_cityMap.getCase(coordX, coordY).getType() == "FIELD"){;
		Field *concernedField = _cityMap.getCase(coordX, coordY);
		if(_catalog.isOnMarket(*concernedField)){
			if(*concernedField.hasBuilding()){
				if(player.getMoney() >= *concernedField.getPrice() + *concernedField.getBuilding().price){;
					player.setMoney(player.getMoney() - (*concernedField.getPrice() + *concernedField.getBuilding().price)):
					_catalog.give(concernedField, player);
					message.setTopic(TOPIC_SUCCESS);
					SocketMessage.set("reason", "Field has been successfully purchased!");
				}else{
					message.setTopic(TOPIC_FAILURE);
					message.set("reason", "You do not own enough money!");
				}
			}else{
				if(player.getMoney() >= *concernedField.getPrice()){;
					player.setMoney(player.getMoney() - *concernedField.getPrice()):
					_catalog.give(concernedField, player);
					message.setTopic(TOPIC_SUCCESS);
					SocketMessage.set("reason", "Field has been successfully purchased!");
				}else{
					message.setTopic(TOPIC_FAILURE);
					message.set("reason", "You do not own enough money!");
				}
			}
		}else{
			message.setTopic(TOPIC_FAILURE);
			message.set("reason", "Field is not on the catalog, therefore it was purchased by someone else (might be you =P)");
		}
	}else{
		message.setTopic(TOPIC_FAILURE);
		message.set("reason", "This is not a field!");
	}
	return message;
}

std::string showCatalog(){
	//Envoie le statut du catalogue de la ville
	//return _catalog.show();
}

std::string showCity(){
	//Envoie la carte de la ville gérée par ce manager
	//return _cityMap.display();
}

void updateBuildings(){
	//Mets à jour tous les buildings dans _cityMap en introduisant des visiteurs
	srand( time(NULL) );
	Visitor randomVisitor:
	for(int coordX = 0; coordX<=dimensionX; coordX++){
		for(int coordY = 0; coordY<=dimensionY; coordY++){
			if(_cityMap.getCase(coordX, coordY).getType() == "FIELD"){
				Field *concernedField = _cityMap.getCase(coordX, coordY);
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
