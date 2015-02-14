#ifndef VISITOR_HPP_
#define VISITOR_HPP_

#include <list>
#include "Location.hpp"
//#include "BuildingType.hpp"


class Visitor{
	Location currentLocation;
	std::list<Location> path;
	//std::list<BuildingType> preference;
	public:
		Visitor();
		void advance();
};

#endif // MAP_HPP_

