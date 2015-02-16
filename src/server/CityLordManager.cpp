#include "CityLordManager.hpp"

void CityLordManager::CityLordManager(){
	_catalog = Catalog();
	_cityMap = Map();
}

void CityLordManager::buildBuilding(Player& player, int coordX, int coordY, std::string buildingType){
	//Regarde si le joueur est le propriétaire de la parcelle:
	//	Si oui, regarde si la parcelle est vide
	//		Si oui, regarde si le joueur a assez d'argent
	//			Si oui, le building est créé et un message est envoyé
	//			Si non, un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
}

void CityLordManager::upgradeBuilding(Player& player, int coordX, int coordY){
	//Regarde si le joueur est le propriétaire de la parcelle et qu'elle contient un bulding:
	//	Si oui, regarde si le building peut être amélioré
	//		Si oui, regarde si le joueur a assez d'argent
	//			Si oui, le building est amélioré et un message est envoyé
	//			Si non, un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
}

void CityLordManager::destroyBuilding(Player& player, int coordX, int coordY){
	//Regarde si le joueur est le propriétaire de la parcelle et qu'elle contient un bulding:
	//	Si oui, regarde si le joueur a assez d'argent
	//		Si oui, le building est amélioré et un message est envoyé
	//		Si non, un message est envoyé
	//	Si non, un message est envoyé
}

void CityLordManager::makeTrade(Player& player1, Player& player2, int coordX, intcoordY){
	//Regarde si le joueur 1 a assez d'argent
	//	Si oui, l'échange est effectué et des messages sont envoyés
	//	Si non, un message est envoyé au joueur 1
}

void CityLordManager::makePurchase(Player& player1, int coordX, int coordY){
	//Regarde si le joueur 1 a assez d'argent
	// Si oui, le cataloque est mis a jour, le joueur obtient la parcelle et un message est envoyé
	// Si non, un message est envoyé
}

void showCatalog(){
	//Envoie un message avec le statut du catalogue
}
