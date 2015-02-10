#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "Case.hpp"
#include "Building.hpp"

class Field{			// public Case
	Building* building;
	public:
		Field();
		Building buildBuilding();
		void destroyBuilding();
		void display();
};

#endif // FIELD_HPP_

