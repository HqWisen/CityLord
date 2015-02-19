#include <iostream>
#include <string>
#include <vector>

#include "Catalog.hpp"

Catalog::Catalog() = default;

void Catalog::putOnMarket(Field* field){
	fieldList.push_back(field);
}

void Catalog::getOffer(Player player,Field* field, int money){
	//if(std::find(fieldList.begin(), fieldList.end(), field) != fieldList.end()){ //field in fieldList){
		//if(*field->owner!=player){
			if(money>=field->getPrice()){
				this->acceptOffer(player, field, money);
			}
		//}
	//}
}

void Catalog::acceptOffer(Player player,Field* field, int money){
	this->give(field,player);
	player.loseMoney(money);
}

void Catalog::give(Field* field,Player player){
	//field->setOwner(player);
	//player.addField(field);
	if(field->hasBuilding()){
		//field->getBuilding()->setOwner(player);
		//player.addBuilding(field->getBuilding());
	}
	//fieldList.remove(field); remove existe?
}

//----getters & setters----
std::vector<Field*> Catalog::getBuyable(){return fieldList;}