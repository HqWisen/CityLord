#ifndef BUILDINGTYPE_HPP_
#define BUILDINGTYPE_HPP_

#include <string>

using namespace std;

class BuildingType{
	public:
		static const BuildingType types[];
        static const int typesLength = 5;
        //
		static const BuildingType BAR;
		static const BuildingType NIGHT_CLUB;
		static const BuildingType SHOP;
        static const BuildingType MUSEUM;
        static const BuildingType HOTEL;

        const std::string NAME;
        const int CONSTRUCTIONCOST;
        const int DESTRUCTIONCOST;
        const int CAPACITY;
        const int DAILYCOST;
        const int ATTRACTIVENESS;
        const int STAYTIME;
        const int OPENTIME;
        const int CLOSETIME;
        const int INCOME;
        const int PRICE;
        const int UPGRADECOST;

        BuildingType() = default;
		BuildingType(const BuildingType&) = default;
		BuildingType(string ,\
					int, int, int, int,
					int, int, int, int,
					int, int, int\
					);
        int getTotalPurchasePrice();
		static BuildingType getTypeByIndex(int);
		static int getIndexByType(BuildingType);
};

#endif // BUILDINGTYPE_HPP_



