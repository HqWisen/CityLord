#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <list>
#include "Visitor.hpp"
#include "BuildingType.hpp"

class Building {
	public:
		int maxCapacity;
		int price;
		int openTime;
		int closeTime;
		int income;
		int attractiveness;
		int dailyCost;
		std::list<Visitor*> visitorList;
		int level;
		int destructionCost;
		BuildingType type;
		int owner; // peut etre string
	
	public:
		Building(int, int, BuildingType, int);
		~Building();
		void receiveVisitor(Visitor);
		void deleteVisitor(Visitor);
		void upgrade();
};

#endif // BUILDING_HPP_
