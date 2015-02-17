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

const BuildingType BuildingType::BAR = BuildingType("BAR",\
	 70000, 25000, 70, 400, 0,\
		3, 12, 2, 30, 35500, 32000);

const BuildingType BuildingType::MUSEUM = BuildingType("MUSEUM",\
	 85000, 30000, 90, 600, 0,\
		3, 10, 18, 15, 38500, 37000);

const BuildingType BuildingType::NIGHT_CLUB = BuildingType("NIGHT CLUB",\
	 90000, 35000, 50, 700, 0,\
	 	5, 21, 6, 69, 49500, 41000);

const BuildingType BuildingType::SHOP = BuildingType("SHOP",\
	 50000, 15000, 40, 200, 0,\
		2, 8, 18, 20, 25500, 19000);
