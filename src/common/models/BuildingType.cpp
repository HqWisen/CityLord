#include <algorithm>
#include "BuildingType.hpp"

BuildingType::BuildingType(string name,\
                int constructionCost, int destructionCost, int capacity, int dailyCost, \
                int attractiveness, int stayTime, int openTime, int closeTime, \
                int income, int price, int upgradeCost):
    NAME(name),\
    CONSTRUCTIONCOST(constructionCost),\
    DESTRUCTIONCOST(destructionCost),\
    CAPACITY(capacity),\
    DAILYCOST(dailyCost),\
    ATTRACTIVENESS(attractiveness),\
    STAYTIME(stayTime),\
    OPENTIME(openTime),\
    CLOSETIME(closeTime),\
    INCOME(income),\
    PRICE(price),\
    UPGRADECOST(upgradeCost) {}

int BuildingType::getTotalPurchasePrice(){
    return CONSTRUCTIONCOST + PRICE;
}

BuildingType BuildingType::getTypeByIndex(int index){
	return types[index];
}
int BuildingType::getIndexByType(BuildingType type){
	for (int i=0; i<typesLength; i++){
        if (types[i].NAME == type.NAME){
			return i;
		}
	}
    return -1;
}

const BuildingType BuildingType::BAR = BuildingType("BAR",\
	 70000, 25000, 70, 400, 0,\
        3, 12, 2, 5000, 35500, 32000);

const BuildingType BuildingType::MUSEUM = BuildingType("MUSEUM",\
	 85000, 30000, 90, 600, 0,\
        3, 10, 18, 4500, 38500, 37000);

const BuildingType BuildingType::NIGHT_CLUB = BuildingType("NIGHTCLUB",\
	 90000, 35000, 50, 700, 0,\
        5, 21, 6, 8900, 49500, 41000);

const BuildingType BuildingType::SHOP = BuildingType("SHOP",\
     50000, 15000, 40, 200, 0,\
        2, 8, 18, 4000, 25500, 19000);

const BuildingType BuildingType::HOTEL = BuildingType("HOTEL",\
     110000, 35000, 100, 950, 0,\
        12, 0, 24, 10000, 40000, 20000);

const BuildingType BuildingType::types[] = {BuildingType::BAR, BuildingType::MUSEUM, BuildingType::NIGHT_CLUB, BuildingType::SHOP, BuildingType::HOTEL};
