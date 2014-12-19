#ifndef VISITOR_HPP_
#define VISITOR_HPP_

#include <list>


class Visitor{
	Location currentLocation;
	std::list<Location> path;
	std::list<BuildingType> preference;
	public:
		Visitor() = default;
		void advance();
};

#endif // MAP_HPP_

