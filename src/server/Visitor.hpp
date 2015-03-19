#ifndef VISITOR_HPP_
#define VISITOR_HPP_

#include <vector>
#include <random>
#include <typeinfo>
#include "../common/models/Building.hpp"
#include "../common/models/Location.hpp"
//#include "BuildingType.hpp"

#include <iostream>

class Visitor{
	Location currentLocation;
	std::vector<Location> path;
	//BuildingType preference;
	std::string preference;
	std::vector<std::string> listOfBuildType = {"BAR","MUSEUM","NIGHT CLUB","SHOP"};
	bool onStandby = false;
	public:
		Visitor(Location); //le spawner donne la localistion
		Location getLoc();
		Location getEndLoc();
		void move();
		bool hasReachedEnd();
		//void moveGUI();
		//void displayGUI();
		bool enter(Building*);
		bool choose(Building*); //Building en paramètre
		void setPath(std::vector<Location>);
		bool passesThrough(Location);
		void setOnStandby(bool);
		bool isOnStandby();
};

#endif // MAP_HPP_

