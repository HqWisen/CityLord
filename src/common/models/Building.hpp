#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
#include "BuildingType.hpp"

using namespace std;

class Building {
    int level;
    int attractiveness;
    int capacity;
    int income;
    int price;
    int destructionCost;
    int dailyCost;
    int openTime;
    int closeTime;
    int visitorCounter;
    std::string status;
    BuildingType type;
    int turnToFinish;
    public:

        Building() = delete;
        Building(BuildingType, int lvl = 1);
        ~Building() = default;
        int getLevel();
        int getAttractiveness();
        int getCapacity();
        int getIncome();
        int getPrice();
        int getDestructionCost();
        int getDailyCost();
        int getOpenTime();
        int getCloseTime();
        int getVisitorCounter();
        BuildingType getType();
        int getTotalPurchasePrice();
		void upgrade();
		bool addVisitor();
		void removeVisitor();
        bool isFull();
        std::string getStatus();
        void setStatus(std::string); 
        int getTurnToFinish();
        void decreaseTurnToFinish();
        void renitTurnToFinish();
};
#endif // BUILDING_HPP_
