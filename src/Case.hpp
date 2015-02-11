#ifndef CASE_HPP_
#define CASE_HPP_

#include "Obstacle.hpp"
#include "Field.hpp"

class Case{
	Obstacle* obs;
	Field* field;
	public:
		Case();
  		void display();	

};

#endif // CASE_HPP_
