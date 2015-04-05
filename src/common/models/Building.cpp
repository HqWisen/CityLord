#include <iostream>
#include <algorithm>
#include "Building.hpp"

using namespace std;

#include <iostream>
#include <algorithm>
#include "Building.hpp"

using namespace std;

Building::Building(BuildingType buildingtype, int lvl) : type(buildingtype){
    level = lvl;
    attractiveness = type.ATTRACTIVENESS;
    capacity = type.CAPACITY;
    income = type.INCOME;
    price = type.PRICE;
    destructionCost = type.DESTRUCTIONCOST;
    dailyCost = type.DAILYCOST;
    openTime = type.OPENTIME;
    closeTime = type.CLOSETIME;
    visitorCounter = 0;
    status = "normal";
    if (level > 1){
        for (int i=1; i<level; i++){
            this->upgrade();
        }
    }
}

int Building::getLevel(){
    return level;
}

int Building::getAttractiveness(){
    return attractiveness;
}

int Building::getCapacity(){
    return capacity;
}

int Building::getIncome(){
    return income;
}

int Building::getPrice(){
    return price;
}

int Building::getDestructionCost(){
    return destructionCost;
}

int Building::getDailyCost(){
    return dailyCost;
}

int Building::getOpenTime(){
    return openTime;
}

int Building::getCloseTime(){
    return closeTime;
}

int Building::getVisitorCounter(){
    return visitorCounter;
}

BuildingType Building::getType(){
    return type;
}

int Building::getTotalPurchasePrice(){
    return type.CONSTRUCTIONCOST + getPrice();
}

void Building::upgrade(){
    capacity += (type.CAPACITY/3);
    income += (type.INCOME/3);
    attractiveness += (type.ATTRACTIVENESS/3);
    dailyCost += (type.DAILYCOST/3);
    destructionCost += (type.DESTRUCTIONCOST/2);
    level += 1;
}

bool Building::addVisitor(){
    if (visitorCounter < capacity){
        visitorCounter += 1;
        return true;
    }
    return false;

}

void Building::removeVisitor(){
    if(visitorCounter > 0){
        visitorCounter -= 1;
    }
}
bool Building::isFull(){
    return visitorCounter == capacity;
}

std::string Building::getStatus(){
    return status;
}