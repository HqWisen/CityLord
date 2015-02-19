#include <iostream>
#include "Field.hpp"

using namespace std;


Field::Field(Location coords){
	typeName = "Field";
	coord = coords;
}

Field::Field(Location coords, Building* newBuilding){
	typeName = "Field";
	coord = coords;
	building = newBuilding;
}

Field::Field(Player* newOwner, Location coords){
	typeName = "Field";
	coord = coords;
	owner = newOwner;
}
Field::Field(Player* newOwner, Location coords, Building* newBuilding){
	typeName = "Field";
	coord = coords;
	owner = newOwner;
	building = newBuilding;
}

string Field::display(){
	char ownerStr = ' ';
	if (this->hasOwner()){
		ownerStr = (owner->getPlayerID());
	}
	if (this->hasBuilding()){
		int type = BuildingType::getIndexByType(getBuilding()->getType());
		int level = getBuilding()->getLevel();
		char buildingStr = ((type*10)+level);
		return ownerStr + "B" + buildingStr;
	}
	else{
		return ownerStr + "F ";
	}
}

void Field::buildBuilding(Building* newBuilding){
	building = newBuilding;
}

//----getters & setters----
void Field::setPrice(int amount){
	price = amount;
}

int Field::getPrice(){
	return price;
}

Player* Field::getOwner(){
	return owner;
}

void Field::setOwner(Player* newOwner){
	owner = newOwner;
}

Building* Field::getBuilding(){
	return building;
}

bool Field::hasOwner(){
	return (owner != nullptr);
}

bool Field::hasBuilding(){
	return (building != nullptr);
}
