#include "Offer.hpp"

Offer::Offer(Player* offeringPlayer, Field* concernedField, int price){
	owner = offeringPlayer;
	ownedField = concernedField;
	offeredPrice = price;
}

Player* Offer::getOwner(){
	return owner;
}

Field* Offer::getField(){
	return ownedField;
}

int Offer::getPrice(){
	return offeredPrice;
}

Offer::~Offer(){
	owner = nullptr;
	ownedField = nullptr;
	delete &offeredPrice;
}

