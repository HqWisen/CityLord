#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"
#include "Player.hpp"
#include "string"

class Field : public Case{			// public Case
	int price = 15000;
	Building* building = nullptr;
	Player* owner = nullptr;
	string color = "";
	public:
		Field(Location);
		Field(Location, Building*);
		Field(Player*, Location);
		Field(Player*, Location, Building*);
		Field(int, Location);
		Field(int, Location, Building*);
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
		string display() override;
		bool isField() override;
		string toString();
};

#endif // FIELD_HPP_

