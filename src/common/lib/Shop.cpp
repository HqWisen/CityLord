
#include <iostream>
#include <algorithm>
#include "Shop.hpp"

using namespace std;

Shop::Shop(int lvl){
	level = lvl;
	visitorCounter = 0;
	maxCapacity = 40;
	price = 50000;
	openTime = 8;
	closeTime = 18;
	income = 20;
	attractiveness = 0;
	dailyCost = 200;
	destructionCost = 15000;
	if (level > 1){
		for (int i=1; i<level; i++){
			this->upgrade();
			level -= 1;
		}
	}
}

/*
const BuildingType BuildingType::SHOP = BuildingType("SHOP",\
	 50000, 15000, 40, 200, 0,\
		2, 8, 18, 20, 25500, 19000);

		BuildingType::BuildingType(string name,\
				int construction, int destruction, int capacity, int daily, \
				int attract, int stay, int open, int close, \
				int gain, int buy, int upgrade):
*/