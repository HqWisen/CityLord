
#include "Field.hpp"

using namespace std;

/* BASIC FIELD */

BasicField::BasicField(Location location) : Case(location){
}

/*
Field::Field(int newColor, Location coords){
    typeName = "Field";
    coord = coords;
    string colorNumber;
    ostringstream convert;
    convert << newColor;
    colorNumber = convert.str();
    color = color="\033[1;"+colorNumber+"m";
}

Field::Field(Location location, Building* newBuilding) : Case(location), building(newBuilding) {
}

Field::Field(int newColor, Location location) : Case(location) {
	string colorNumber;
	ostringstream convert;
	convert << newColor;
	colorNumber = convert.str();
	color = color="\033[1;"+colorNumber+"m";
}

Field::Field(int newColor, Location location, Building* newBuilding) : Case(location), building(newBuilding) {
	string colorNumber;
	ostringstream convert;
	convert << newColor;
	colorNumber = convert.str();
	color = color="\033[1;"+colorNumber+"m";
}
*/

string BasicField::print(){
    string ownerStr = " ";
    if (hasOwner()){
        ownerStr = to_string(getOwnerID());
    }
    if (hasBuilding()){
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

void BasicField::buildBuilding(BuildingType buildingType){
    building = new Building(buildingType);
}

/*
void BasicField::buildBuilding(string buildingType){
    if(buildingType=="Bar"){building = new Bar();}
    else if(buildingType=="Shop"){building = new Shop();}
    else if(buildingType=="Museum"){building = new Museum();}
    else if(buildingType=="NightClub"){building = new NightClub();}
}
*/

void BasicField::destroyBuilding(){
    delete building;
    building = nullptr;
}

void BasicField::setPrice(int amount){
    price = amount;
}

int BasicField::getPrice(){
    return price;
}

Building* BasicField::getBuilding(){
    return building;
}

bool BasicField::hasBuilding(){
    return (building != nullptr);
}

string BasicField::getOwnerColor(){
    return Player::COLOR[getOwnerID()];
}


/* FIELD */

Field::Field(Location location) : BasicField(location){
}


Player* Field::getOwner(){
    return owner;
}

void Field::setOwner(Player* newOwner){
    owner = newOwner;
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

int Field::getOwnerID(){
    return owner->getPlayerID();
}

bool Field::hasOwner(){
    return owner != nullptr;
}

/* CLIENTFIELD */

ClientField::ClientField(Location location) : BasicField(location){
}

int ClientField::getOwnerID(){
    return ownerid;
}

void ClientField::setOwnerID(int id){
    ownerid = id;
}

bool ClientField::hasOwner(){
    return ownerid != -1;
}

