#ifndef NEIGHBORHOOD_HPP_
#define NEIGHBORHOOD_HPP_

#include "Map.hpp"
#include "Case.hpp"


class Neighborhood{
	//const int nombreDeCase;
	Case cases[];
	public:
		Neighborhood();
		void display();
};

#endif // NEIGHBORHOOD_HPP_

