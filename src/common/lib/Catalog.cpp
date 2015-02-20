#include <iostream>
#include <string>
#include <vector>

#include "Catalog.hpp"

void Catalog::putOnMarket(Field* field){
	fieldVector.push_back(field);
}

std::vector<Field*> Catalog::getPurchasableFields(){
	return fieldVector;
}

void Catalog::give(Field* field,Player* player){
	field->setOwner(player);
	player->addField(field);
	if(field->hasBuilding()){
		// TODO 
		//field->getBuilding()->setOwner(player);
		//player.addBuilding(field->getBuilding());
	}
	std::vector<Field*>::iterator tmp;
	for (std::vector<Field*>::iterator it = fieldVector.begin(); it != fieldVector.end(); it++){
		if(*(it) == field){
			tmp = it;
			break;
		}
	}
	fieldVector.erase(tmp);	
}

bool Catalog::isOnMarket(Field* field){
	for (std::vector<Field*>::iterator it = fieldVector.begin(); it != fieldVector.end(); it++){
		if(*(it) == field){
			return true;
		}
	}
	return false;
}

/*
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



//----getters & setters----
std::vector<Field*> Catalog::getBuyable(){return fieldList;}
*/
