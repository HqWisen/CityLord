#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <sstream>
#include "Case.hpp"
#include "BuildingType.hpp"
#include "Player.hpp"
#include "Building.hpp"
#include <string>

class Field : public Case{			// public Case
    int price = 15000;
    Building* building = nullptr;
    Player* owner = nullptr;
    string color = "";
	public:
		Field(Location);
        std::string print() override;
        void buildBuilding(BuildingType);
		void destroyBuilding();
		int getPrice();
		void setPrice(int);
		Player* getOwner();
		string getColor();
		void setOwner(Player*);
		Building* getBuilding();
		bool hasOwner();
		bool hasColor();
		bool hasBuilding();
        string toString();
};

#endif // FIELD_HPP_

