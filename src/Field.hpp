#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"

class Field{			// public Case
	Building* building;
	public:
		Field();
		void buildBuilding(Building build); // type Building
		void destroyBuilding();
		void display();
};

#endif // FIELD_HPP_

