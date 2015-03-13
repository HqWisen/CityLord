#ifndef VISITOR_HPP_
#define VISITOR_HPP_

#include <vector>
#include <random>
#include <typeinfo>
#include "Building.hpp"
#include "Location.hpp"
//#include "BuildingType.hpp"

#include <iostream>

class Visitor{
	Location currentLocation;
	std::vector<Location> path;
	//BuildingType preference;
	std::string preference;
	std::vector<std::string> listOfBuildType = {"BAR","MUSEUM","NIGHT CLUB","SHOP"};
	unsigned count = 0;
	public:
		Visitor(Location); //le spawner donne la localistion
		Location getLoc();
		void move();
		//void moveGUI();
		//void displayGUI();
		bool enter(Building*);
		bool choose(Building*); //Building en paramètre
		void setPath(std::vector<Location>);
};

#endif // MAP_HPP_

