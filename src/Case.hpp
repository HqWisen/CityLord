#ifndef CASE_HPP_
#define CASE_HPP_

//#include "Obstacle.hpp"
//#include "Field.hpp"
//#include "Road.hpp"
#include "Location.hpp"

class Case{
	//Obstacle* obs;
	//Field* field;
	//Road* road;
	Location coord;
	public:
		//Case(Obstacle obs);
		//Case(Field field);
		//Case(Road road);
  		void display();
  		Location getCoord();
};

#endif // CASE_HPP_
