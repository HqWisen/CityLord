#include <algorithm>
#include "BuildingType.hpp"

BuildingType::BuildingType(string name,\
				int construction, int destruction, int capacity, int daily, \
				int attract, int stay, int open, int close, \
				int gain, int buy, int upgrade):
	buildingName(name),\
	constructionCost(construction),\
	destructionCost(destruction),\
	maxCapacity(capacity),\
	dailyCost(daily),\
	attractiveness(attract),\
	stayTime(stay),\
	openTime(open),\
	closeTime(close),\
	income(gain),\
	price(buy),\
	upgradeCost(upgrade) {}

BuildingType BuildingType::getTypeByIndex(int index){
	return types[index];
}
int BuildingType::getIndexByType(BuildingType type){
	for (int i=0; i<typesLength; i++){
		if (types[i].buildingName == type.buildingName){
			return i;
		}
	}
    return -1;
}

const BuildingType BuildingType::BAR = BuildingType("BAR",\
	 70000, 25000, 70, 400, 0,\
		3, 12, 2, 30, 35500, 32000);

const BuildingType BuildingType::MUSEUM = BuildingType("MUSEUM",\
	 85000, 30000, 90, 600, 0,\
		3, 10, 18, 15, 38500, 37000);

const BuildingType BuildingType::NIGHT_CLUB = BuildingType("NIGHTCLUB",\
	 90000, 35000, 50, 700, 0,\
	 	5, 21, 6, 69, 49500, 41000);

const BuildingType BuildingType::SHOP = BuildingType("SHOP",\
     50000, 15000, 40, 200, 0,\
        2, 8, 18, 20, 25500, 19000);

const BuildingType BuildingType::HOTEL = BuildingType("HOTEL",\
     110000, 35000, 100, 450, 0,\
        12, 0, 24, 100, 40000, 20000);

const BuildingType BuildingType::types[] = {BuildingType::BAR, BuildingType::MUSEUM, BuildingType::NIGHT_CLUB, BuildingType::SHOP, BuildingType::HOTEL};
