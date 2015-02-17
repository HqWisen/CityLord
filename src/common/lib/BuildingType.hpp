#ifndef BUILDINGTYPE_HPP_
#define BUILDINGTYPE_HPP_

#include <string>

using namespace std;

class BuildingType{
public:
	static const BuildingType BAR;
	static const BuildingType NIGHT_CLUB;
	static const BuildingType SHOP;
	static const BuildingType MUSEUM;

	std::string buildingName;
	int constructionCost;
	int destructionCost;
	int maxCapacity;
	int dailyCost;
	int attractiveness;
	int stayTime;
	int openTime;
	int closeTime;
	int income;
	int price;
	int upgradeCost;
	BuildingType(string ,\
				int, int, int, int,
				int, int, int, int,
				int, int, int\
				);
};


/*extern BuildingType BAR;
	BAR.name = "BAR";
	BAR.constructionCost;
	BAR.destructionCost;
	BAR.capacity;
	BAR.dailyCost;
	BAR.attractiveness;
	BAR.stayTime = 3 heures;
	BAR.openTime;
	BAR.closeTime;
	BAR.income;
	BAR.price;
	BAR.upgradeCost;

extern BuildingType MUSEUM;
	MUSEUM.name = "MUSEUM";
	MUSEUM.constructionCost;
	MUSEUM.destructionCost;
	MUSEUM.capacity;
	MUSEUM.dailyCost;
	MUSEUM.attractiveness;
	MUSEUM.openTime;
	MUSEUM.closeTime;
	MUSEUM.income;
	MUSEUM.price;
	MUSEUM.upgradeCost;

extern BuildingType NIGHT_CLUB;
	NIGHT_CLUB.name = "NIGHT CLUB";
	NIGHT_CLUB.constructionCost;
	NIGHT_CLUB.destructionCost;
	NIGHT_CLUB.capacity;
	NIGHT_CLUB.dailyCost;
	NIGHT_CLUB.attractiveness;
	NIGHT_CLUB.openTime;
	NIGHT_CLUB.closeTime;
	NIGHT_CLUB.income;
	NIGHT_CLUB.price;
	NIGHT_CLUB.upgradeCost;

extern BuildingType SHOP;
	SHOP.name = "SHOP";
	SHOP.constructionCost;
	SHOP.destructionCost;
	SHOP.capacity;
	SHOP.dailyCost;
	SHOP.attractiveness;
	SHOP.openTime;
	SHOP.closeTime;
	SHOP.income;
	SHOP.price;
	SHOP.upgradeCost;*/

#endif // BUILDINGTYPE_HPP_



