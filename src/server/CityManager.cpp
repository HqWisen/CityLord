#include "CityManager.hpp"


CityManager::CityManager(std::string mapname) : cityMap(mapname){
	std::cout<<"CityManager created with MapName "<<mapname<<std::endl;
	cityMap.display();
	//_catalog = Catalog();
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
	Case* concernedCase = _cityMap.getCase(coordX, coordY);
	if(concernedCase.getOwner() == player){
		if(!concernedCase.hasBuilding()){
			if(player.getMoney() >= buildingType.getPrice()){
				player.setMoney(player.getMoney() - buildingType.getPrice());
				Building building = Building(buildingType, player);
				concernedCase.setBuilding(building);
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
	Case* concernedCase = _cityMap.getCase(coordX, coordY);
	if(concernedCase.getOwner() == player){
		if(concernedCase.hasBuilding()){
			Building concernedBuilding = concernedCase.getBuilding();
			if(player.getMoney() >= concernedBuilding.getUpgradeCost()){
				player.setMoney(player.getMoney() - buildingType.getUpdateCost());
				concernedBuilding.upgrade();
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
	return message;
}

SocketMessage CityLordManager::destroyBuilding(Player& player, int coordX, int coordY){
	//Regarde si le joueur est le propriétaire de la parcelle et qu'elle contient un bulding:
	//	Si oui, regarde si le joueur a assez d'argent
	//		Si oui, le building est amélioré et un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
	SocketMessage message = SocketMessage();
	Case* concernedCase = _cityMap.getCase(coordX, coordY);
	if(concernedCase.getOwner() == player){
		if(concernedCase.hasBuilding()){
			Building concernedBuilding = concernedCase.getBuilding();
			if(player.getMoney() >= concernedBuilding.getDestructionCost()){
				player.setMoney(player.getMoney() - buildingType.getDestructionCost());
				concernedBuilding.destroy();
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
	return message;
}

SocketMessage CityLordManager::makeTrade(Player& player1, Player& player2, int coordX, int coordY, int offeredMoney){
	//Regarde si le joueur 1 a assez d'argent
	//	Si oui, l'échange est effectué et des messages sont envoyés
	//	Si non, un message est envoyé au joueur 1
	SocketMessage message = SocketMessage();
	Case* concernedCase = _cityMap.getCase(coordX, coordY);
	if(concernedCase.getOwner() == player2){
		if(player1.getMoney() >= offeredMoney){
			player1.setMoney(player1.getMoney() - offeredMoney);
			player2.setMoney(player2.getMoney() + offeredMoney);
			concernedCase.setOwner(player1);
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
	return message;*
}

SocketMessage CityLordManager::makePurchase(Player& player, int coordX, int coordY){
	//Regarde si le joueur 1 a assez d'argent
	// Si oui, le cataloque est mis a jour, le joueur obtient la parcelle et un message est envoyé
	// Si non, un message est envoyé
	SocketMessage message = SocketMessage();
	Case* concernedCase = _cityMap.getCase(coordX, coordY);
	if(_catalog.isOnMarket(concernedCase)){
		if(player.getMoney() >= concernedCase.getPrice());
			player.setMoney(player.getMoney() - concernedCase.getPrice()):
			concernedCase.setOwner(player);
			message.setTopic(TOPIC_SUCCESS);
			SocketMessage.set("reason", "Field has been successfully purchased!");
		}else{
			message.setTopic(TOPIC_FAILURE);
			message.set("reason", "You do not own enough money!");
		}
	}else{
		message.setTopic(TOPIC_FAILURE);
		message.set("reason", "Field is not on the catalog, therefore it was purchased by someone else (might be you =P)");
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
*/
