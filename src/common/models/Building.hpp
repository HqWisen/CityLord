#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
#include "BuildingType.hpp"

using namespace std;

class Building {
    private:
        string name;
        int constructionCost;
        int destructionCost;
        int openTime;
        int stayTime;
        int closeTime;
        int income;
        int price;
        int maxCapacity;
        int attractiveness;
        int dailyCost;
        int visitorCounter;
        int level;
        int upgradeCost;
        BuildingType type;

    public:
        Building(BuildingType, int level = 1);
        Building();
        ~Building() = default;
        int getLevel();
        int getPrice(){return this->price;};
		int getDestructionCost(){return this->destructionCost;};
        int getDailyCost(){return this->dailyCost;};
        BuildingType getType();
		void upgrade();
		bool addVisitor();
		void removeVisitor();
        bool isFull(){return visitorCounter==maxCapacity;};
        int getIncome();

};
#endif // BUILDING_HPP_
