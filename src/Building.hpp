#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <list>
#include "Visitor.hpp"

class Building{
	int maxcapacity;
	int capacity;
	int price;
	int openTime;
	int closeTime;
	int income;
	int attractiveness;
	int dailyCost;
	std::list<Visitor*> visitorList;
	int level;
	int constructionCost;
	int destructionCost;
	//BuildingType type;
	
	public:
		Building();
		void deleteVisitor(Visitor&);
		void receiveVisitor(Visitor&);
		void upgrade();
		void display();
};

#endif // BUILDING_HPP_
