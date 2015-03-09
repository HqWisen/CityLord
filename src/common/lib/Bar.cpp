
#include <iostream>
#include <algorithm>
#include "Bar.hpp"

using namespace std;

Bar::Bar(int lvl){
	level = lvl;
	visitorCounter = 0;
	maxCapacity = 70;
	price = 70000;
	openTime = 12;
	closeTime = 2;
	income = 30;
	attractiveness = 0;
	dailyCost = 400;
	destructionCost = 25000;
	if (level > 1){
		for (int i=1; i<level; i++){
			this->upgrade();
			level -= 1;
		}
	}
}

/*
const BuildingType BuildingType::BAR = BuildingType("BAR",\
	 70000, 25000, 70, 400, 0,\
		3, 12, 2, 30, 35500, 32000);

		BuildingType::BuildingType(string name,\
				int construction, int destruction, int capacity, int daily, \
				int attract, int stay, int open, int close, \
				int gain, int buy, int upgrade):
*/