#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"
#include "Player.hpp"

class Field : public Case{			// public Case
	int price = 15000;
	Building* building = nullptr;
	Player* owner = nullptr;
	public:
		Field(Location);
		Field(Location, Building*);
		Field(Player*, Location);
		Field(Player*, Location, Building*);
		void buildBuilding(Building*);
		void destroyBuilding();
		int getPrice();
		void setPrice(int);
		Player* getOwner();
		void setOwner(Player*);
		Building* getBuilding();
		bool hasOwner();
		bool hasBuilding();
		string display() override;
		bool isField() override;
		string toString();
};

#endif // FIELD_HPP_

