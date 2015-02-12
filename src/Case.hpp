#ifndef CASE_HPP_
#define CASE_HPP_

#include "Obstacle.hpp"
#include "Field.hpp"
#include "Road.hpp"

class Case{
	Obstacle* obs;
	Field* field;
	Road* road;
	public:
		Case(Obstacle obs);
		Case(Field field);
		Case(Road road);
  		void display();	
};

#endif // CASE_HPP_
