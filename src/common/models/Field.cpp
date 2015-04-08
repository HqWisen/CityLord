
#include "Field.hpp"


using namespace std;

/* BASIC FIELD */

BasicField::BasicField(Location location) : Case(location), price(15000), building(nullptr), showOwnerColor(false){
}

string BasicField::print(){
    string ownerStr = " ";
    if (hasOwner()){
        ownerStr = to_string(getOwnerID());
    }
    if (hasBuilding()){
        int type = BuildingType::getIndexByType(this->getBuilding()->getType());
        int level = this->getBuilding()->getLevel();
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

string BasicField::getImageName(){
    std::string imagename, buildingName, buildingStatus;
    if(hasBuilding()){
       buildingName = building->getType().NAME;
       std::transform(buildingName.begin(), buildingName.end(), buildingName.begin(), ::tolower);
       imagename = buildingName;
       buildingStatus = building->getStatus();
       cout<<buildingStatus<<endl;
       if(buildingStatus == "hypotheque"){
            imagename += "_";
            imagename += "hypotheque";
        }
        else if(buildingStatus == "construction"){
            imagename += "_";
            imagename += "construction";
        }
        else if(buildingStatus == "destruction"){
            imagename += "_";
            imagename += "destruction";
        }
    }
    else{
        imagename = "base";
    }
    if(showOwnerColor){
        if(hasOwner()){
            if(hasBuilding()){
                if(buildingStatus == "normal"){
                    imagename += "_" + Player::COLORNAME[getOwnerID()];
                }
                else{
                    imagename = buildingName;
                    imagename += "_" + Player::COLORNAME[getOwnerID()];
                }
            }
            else{
                imagename += "_" + Player::COLORNAME[getOwnerID()];
            }
        }          
        else{
            imagename = "grass";
        }
    }
    return imagename;
}

void BasicField::setShowOwnerColor(bool show){
    showOwnerColor = show;
}

bool BasicField::isField(){
    return true;
}

void BasicField::buildBuilding(BuildingType buildingType, int level){
    building = new Building(buildingType, level);
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
    if (building != nullptr){
        delete building;
        building = nullptr;
    }
}

void BasicField::setPrice(int amount){
    price = amount;
}

int BasicField::getPrice(){
    return price;
}

int BasicField::getOfferedPrice(){
	return offeredPrice;
}

void BasicField::setOfferedPrice(int newPrice){
	offeredPrice = newPrice;
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

int BasicField::getTotalPurchasePrice(){
    int total = 0;
    total += getPrice();
    if(hasBuilding()){
        total += building->getTotalPurchasePrice();
    }
    return total;
}


/* FIELD */

Field::Field(Location location) : BasicField(location), owner(nullptr){
}


Player* Field::getOwner(){
    return owner;
}

void Field::setOwner(Player* newOwner){
    owner = newOwner;
}


string Field::toString(float mult){
    string result;
    int res = static_cast<int>(price*mult);
    result += "Price : " + std::to_string(res);
    result += " - ";
    result += "Owner : ";
    if(hasOwner()){
        result += owner->getNickName();
        if(offeredPrice != 0){
			result += " - ";
			result += "Offered for : " + std::to_string(offeredPrice);
		}
    }else{
        result += "no owner";
    }
    if(hasBuilding()){
        result += " # "+building->getType().NAME;
        std::string buildingStatus = building->getStatus();
        if(buildingStatus == "hypotheque"){
            result += "  **Hypothecated**";
        }
        else if(buildingStatus == "construction"){
            result += "  **Being constructed**";
        }
        else if(buildingStatus == "destruction"){
            result += "  **Being destroyed**";
        }
    }
    return result;
}

int Field::getOwnerID(){
    return owner->getPlayerID();
}

bool Field::hasOwner(){
    return owner != nullptr;
}

SocketMessage Field::infoHasSocketMessage(){
    SocketMessage message;
    if(hasOwner()){
        message.set("ownername", getOwner()->getNickName());
        message.set("ownerid", std::to_string(getOwnerID()));
        message.set("ownercolor", Player::COLORNAME[getOwnerID()]);
        message.set("offeredprice", std::to_string(offeredPrice));
    }else{
        message.set("ownername", "No owner");
        message.set("ownerid", "-");
        message.set("ownercolor", "-");
    }
    if(hasBuilding()){
        message.set("level", std::to_string(building->getLevel()));
        message.set("attractiveness", std::to_string(building->getAttractiveness()));
        message.set("capacity", std::to_string(building->getCapacity()));
        message.set("income", std::to_string(building->getIncome()));
        message.set("price", std::to_string(building->getPrice()));
        message.set("destructioncost", std::to_string(building->getDestructionCost()));
        message.set("dailycost", std::to_string(building->getDailyCost()));
        message.set("opentime", std::to_string(building->getOpenTime()));
        message.set("closetime", std::to_string(building->getCloseTime()));
        message.set("visitorcounter", std::to_string(building->getVisitorCounter()));
        message.set("typeindex", std::to_string(BuildingType::getIndexByType(building->getType())));
    }
    message.set("fieldprice", std::to_string(price));
    return message;
}

/* CLIENTFIELD */

ClientField::ClientField(Location location) : BasicField(location), ownerid(-1){
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

