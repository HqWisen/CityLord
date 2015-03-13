#include <iostream>
#include <algorithm>
#include "Building.hpp"

using namespace std;

Building::Building(BuildingType buildingtype, int lvl) : type(buildingtype){
    level = lvl;
	visitorCounter = 0;
    maxCapacity = type.maxCapacity;
    price = type.price;
    openTime = type.openTime;
    closeTime = type.closeTime;
    income = type.income;
    attractiveness = type.attractiveness;
    dailyCost = type.dailyCost;
    destructionCost = type.destructionCost;
    if (level > 1){
        for (int i=1; i<level; i++){
            this->upgrade();
        }
    }
}

Building::Building(){}

int Building::getLevel(){
	return level;
}

BuildingType Building::getType(){
	return type;
}

/*void Building::upgrade(){
    maxCapacity += (maxCapacity/2);
    income += (income/2);
    attractiveness += (attractiveness/2);
    dailyCost += (dailyCost/1.75);
    level += 1;
    destructionCost += (destructionCost/2);
}*/

void Building::upgrade(){
	maxCapacity += type.maxCapacity;
	income += type.income;
	attractiveness += ((type.attractiveness)/2);
	dailyCost += ((type.dailyCost)/1.75);
	level += 1;
	destructionCost += ((type.destructionCost)/2);
}

bool Building::addVisitor(){
	if (visitorCounter < maxCapacity){
		visitorCounter += 1;
		return true;
	}
	return false;
	
}

void Building::removeVisitor(){
	if{visitorCounter > 0{
		visitorCounter -= 1;
	}
}
