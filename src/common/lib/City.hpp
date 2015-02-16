#ifndef CITY_HPP_
#define CITY_HPP_

#include <string>
#include <time.h>

class City{
	
	std::string name;
	std::time_t time;
	unsigned int nbPlayer;
	unsigned int maxSpawn;
	Map map;
	std::list<Visitor> visitorList;
	std::list<Player*> playerList;
	Catalog catalog;
	
	public:
		City() = default;
		void addVisitor();
		Visitor generateVisitor();
};

#endif // CITY_HPP_

