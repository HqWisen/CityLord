#include <iostream>
#include <algorithm>
#include "Building.hpp"

using namespace std;

//Erase-Remove idiom for vector 
/*
template<typename T>
inline void removeElem(vector<T> & vect, const T & item)
{
    vect.erase(remove(vect.begin(), vect.end(), item), vect.end());
}
*/
Building::Building(BuildingType buildingtype, int lvl) : type(buildingtype){
	level = lvl;
	maxCapacity = type.maxCapacity;
	price = type.price;
	openTime = type.openTime;
	closeTime = type.closeTime;
	income = type.income;
	attractiveness = type.attractiveness;
	dailyCost = type.dailyCost;
	destructionCost = type.destructionCost;
	//
	/*if (level > 1){
		for (int i=1; i<level; i++){
			this->upgrade();
			level -= 1;
		}
	}*/
}

int Building::getLevel(){
	return level;
}
BuildingType Building::getType(){
	return type;
}

void Building::upgrade(){
	maxCapacity += type.maxCapacity;
	income += type.income;
	attractiveness += ((type.attractiveness)/2);
	dailyCost += ((type.dailyCost)/1.75);
	level += 1;
	destructionCost += ((type.destructionCost)/2);
}

/*

void Building::receiveVisitor(Visitor* guest){
	visitorList.push_back(guest);
}

void Building::deleteVisitor(Visitor* guest){
	removeElem(visitorList, guest);
}




}*/
