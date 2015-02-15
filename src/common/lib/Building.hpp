#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <list>
#include "Case.hpp"
#include "Visitor.hpp"
#include "BuildingType.hpp"

class Building : public Case{
	int maxcapacity;
	int price;
	int openTime;
	int closeTime;
	int income;
	int attractiveness;
	int dailyCost;
	std::list<Visitor*> visitorList;
	int level;
	int destructionCost;
	int owner; // peut etre string
	BuildingType type;
	
	public:
		Building(int, int, BuildingType, int);
		~Building();
		void receiveVisitor(Visitor);
		void deleteVisitor(Visitor);
		void upgrade();
		void display();
};

#endif // BUILDING_HPP_
