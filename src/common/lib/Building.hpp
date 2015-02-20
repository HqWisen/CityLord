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
		std::vector<Visitor*> visitorVector;
		int level;
		int destructionCost;
		BuildingType type;
	
	public:
		Building(BuildingType, int level = 1);
		~Building() = default;
		int getLevel();
		BuildingType getType();
		int getPrice(){return price;};
		int getDestructionCost(){return destructionCost;};
		void upgrade();
		/*void receiveVisitor(Visitor*);
		void deleteVisitor(Visitor*);
*/
};
#endif // BUILDING_HPP_
