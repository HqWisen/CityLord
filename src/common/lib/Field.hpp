#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"
#include "Player.hpp"

class Field : public Case{			// public Case
	Building* building = nullptr;
	int price;
	Player* owner;

	public:
		Field(Location);
		void buildBuilding(Building* build); // type Building
		void destroyBuilding();
		string display();

		int getPrice();
		void setPrice(int);
		Player* getOwner();
		void setOwner(Player*);
		Building* getBuilding();
		void setBuilding(Building*);
		bool hasBuilding();
};

#endif // FIELD_HPP_

