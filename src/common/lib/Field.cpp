#include <iostream>
#include <sstream>
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
	color = newOwner->getColor();
}

Field::Field(Player* newOwner, Location coords, Building* newBuilding){
	typeName = "Field";
	coord = coords;
	owner = newOwner;
	color = newOwner->getColor();
	building = newBuilding;
}

Field::Field(int newColor, Location coords){
	typeName = "Field";
	coord = coords;
	string colorNumber;
	ostringstream convert;
	convert << newColor;
	colorNumber = convert.str();
	color = color="\033[1;"+colorNumber+"m";
}

Field::Field(int newColor, Location coords, Building* newBuilding){
	typeName = "Field";
	coord = coords;
	string colorNumber;
	ostringstream convert;
	convert << newColor;
	colorNumber = convert.str();
	color = color="\033[1;"+colorNumber+"m";
	building = newBuilding;
}

string Field::display(){
	string ownerStr = " ";
	if (this->hasOwner()){
		ownerStr = to_string(owner->getPlayerID());
	}
	if (this->hasBuilding()){
		int type = BuildingType::getIndexByType(getBuilding()->getType());
		int level = getBuilding()->getLevel();
		if (level == 10){
			level = 0;
		}
		char key = (((type+2)*10)+level);
		string buildingStr;
		stringstream temp_string;
		temp_string << key;
		temp_string >> buildingStr;
		return ownerStr + "B" + buildingStr;
	}
	else{
		return (ownerStr + "F ");
	}
}

bool Field::isField(){
	return true;
}

void Field::buildBuilding(BuildingType buildingType){
	building = new Building(buildingType);
}

void Field::destroyBuilding(){
	delete building;
	building = nullptr;
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

string Field::getColor(){
	return color;
}

void Field::setOwner(Player* newOwner){
	owner = newOwner;
	color = newOwner->getColor();
}

Building* Field::getBuilding(){
	return building;
}

bool Field::hasOwner(){
	return (owner != nullptr);
}

bool Field::hasColor(){
	return (color != "");
}

bool Field::hasBuilding(){
	return (building != nullptr);
}

string Field::toString(){
	string result;
	result += "Price : "+ std::to_string(price);
	result += " - ";
	result += "Owner : ";
	if(hasOwner()){
		result += owner->getNickName();
	}else{
		result += "no owner";
	}
	if(hasBuilding()){
		result += "# "+building->getType().buildingName;
	}
	return result;
}

