#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"

class Field : public Case{			// public Case
	Building* building;
	int price;
	//int-char-string-user ? owner;
	public:
		Field(Location);
		void buildBuilding(Building build); // type Building
		void destroyBuilding();
		void display();

		int getPrice();
		void setPrice(int);
		//int-char-string-user ? getOwner();
		//void setOwner(int-char-string-user?);
};

#endif // FIELD_HPP_

