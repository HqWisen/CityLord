#include <iostream>
#include "Building.hpp"

using namespace std;

Building::Building(int x, int y, BuildingType building, int player) : type(building), owner(player){
	level = 1;

	maxCapacity = type.maxCapacity;
	price = type.price;
	openTime = type.openTime;
	closeTime = type.closeTime;
	income = type.income;
	attractiveness = type.attractiveness;
	dailyCost = type.dailyCost;
	destructionCost = type.destructionCost;
}

Building::~Building(){
	owner = nullptr;
	type = nullptr;
	level = 0;

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

void Building::receiveVisitor(Visitor){
	//visitorList.add(Visitor);
	//Player.money += income;
}

void Building::deleteVisitor(Visitor){
	//visitorList.remove(Visitor);
}

void Building::upgrade(){
	//Player.money -= (type.upgradeCost)*level;
	//maxcapacity += type.capacity;
	//income += type.income;
	//attractiveness += (type.attractiveness)/2;
	//dailyCost += (type.dailyCost)/2;
	//level += 1;
	//destructionCost += (type.destructionCost)/2;
}

int main(){
	return 0;
}
