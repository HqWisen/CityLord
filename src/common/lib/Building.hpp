#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
#include "Visitor.hpp"
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
		std::vector<Visitor*> visitorList;
		int level;
		int destructionCost;
		BuildingType type;
	
	public:
		Building(BuildingType, int);
		~Building();
		void receiveVisitor(Visitor*);
		void deleteVisitor(Visitor*);
		void upgrade();
		int getLevel();
		int getPrice(){return price;};
		BuildingType getType();
};

#endif // BUILDING_HPP_
