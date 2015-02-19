#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"
#include "Player.hpp"

class Field : public Case{			// public Case
	Building* building = nullptr;
	int price = 15000;
	Player* owner = nullptr;

	public:
		Field(Location);
		Field(Location, Building*);
		Field(Player*, Location);
		Field(Player*, Location, Building*);
		void buildBuilding(Building*);
		void destroyBuilding();
		string display();

		int getPrice();
		void setPrice(int);
		Player* getOwner();
		void setOwner(Player*);
		Building* getBuilding();

		bool hasOwner();
		bool hasBuilding();
};

#endif // FIELD_HPP_

