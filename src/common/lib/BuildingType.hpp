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

#endif // BUILDINGTYPE_HPP_



