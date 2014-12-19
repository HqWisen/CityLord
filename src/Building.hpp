#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <list>

class Building{
	const int MAXCAPACITY;
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
	BuildingType type;
	
	public:
		Building() = default;
		void deleteVisitor(Visitor&);
		void receiveVisitor(Visitor&);
		void upgrade();
};

#endif // BUILDING_HPP_
