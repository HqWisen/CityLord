#ifndef BUILDINGTYPE_HPP_
#define BUILDINGTYPE_HPP_

#include <string>

using namespace std;

class BuildingType{
	public:
		static const BuildingType types[];
		static const int typesLength = 4;
        //
		static const BuildingType BAR;
		static const BuildingType NIGHT_CLUB;
		static const BuildingType SHOP;
        static const BuildingType MUSEUM;
        static const BuildingType HOTEL;

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

        BuildingType() = default;
		BuildingType(const BuildingType&) = default;
		BuildingType(string ,\
					int, int, int, int,
					int, int, int, int,
					int, int, int\
					);
		static BuildingType getTypeByIndex(int);
		static int getIndexByType(BuildingType);
};

#endif // BUILDINGTYPE_HPP_



