#ifndef VISITOR_HPP_
#define VISITOR_HPP_

#include <vector>
#include <random>
#include "Location.hpp"

//#include "Building.hpp"
//#include "BuildingType.hpp"

class Visitor{
	Location currentLocation;
	std::vector<Location> path;
	//BuildingType preference;
	std::string preference;
	std::vector<std::string> listOfBuildType = {"BAR","MUSEUM","NIGHT CLUB","SHOP"};
	public:
		Visitor(Location); //le spawner donne la localistion
		~Visitor();
		void move();
		void moveGUI();
		void displayGUI();
		void enter(Building);
		std::vector<Location> getWay();
		bool choose(); //Building en paramètre
};

#endif // MAP_HPP_

