#include <iostream>
#include <algorithm>
#include "Building.hpp"

using namespace std;

//Erase-Remove idiom for vector 
template<typename T>
inline void removeElem(vector<T> & vect, const T & item)
{
    vect.erase(remove(vect.begin(), vect.end(), item), vect.end());
}

Building::Building(BuildingType building, int lvl=1) : type(building){
	level = lvl;
	//
	maxCapacity = type.maxCapacity;
	price = type.price;
	openTime = type.openTime;
	closeTime = type.closeTime;
	income = type.income;
	attractiveness = type.attractiveness;
	dailyCost = type.dailyCost;
	destructionCost = type.destructionCost;
	//
	if (level > 1){
		for (int i=1; i<level; i++){
			this->upgrade();
		}
	}
}

Building::~Building(){
	level = 0;
	//
	maxCapacity = 0;
	price = 0;
	openTime = 0;
	closeTime = 0;
	income = 0;
	attractiveness = 0;
	dailyCost = 0;
	destructionCost = 0;
	visitorList.clear();
}

void Building::receiveVisitor(Visitor* guest){
	visitorList.push_back(guest);
}

void Building::deleteVisitor(Visitor* guest){
	removeElem(visitorList, guest);
}

void Building::upgrade(){
	maxCapacity += type.maxCapacity;
	income += type.income;
	attractiveness += ((type.attractiveness)/2);
	dailyCost += ((type.dailyCost)/1.75);
	level += 1;
	destructionCost += ((type.destructionCost)/2);
}

int Building::getLevel(){
	return level;
}

BuildingType Building::getType(){
	return type;
}
