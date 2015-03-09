#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
#include "BuildingType.hpp"

using namespace std;

class Building {
	public:
		int maxCapacity;
		int price;
		int openTime;
		int closeTime;
		int income;
		int attractiveness;
		int dailyCost;
		int visitorCounter;
		int level;
		int destructionCost;
		BuildingType type;
	
	public:
		Building(BuildingType, int level = 1);
		Building();
		~Building() = default;
		int getLevel();
		BuildingType getType();
		int getPrice(){return this->price;};
		int getDestructionCost(){return this->destructionCost;};
		void upgrade();
		bool addVisitor();
		void removeVisitor();

};
#endif // BUILDING_HPP_
