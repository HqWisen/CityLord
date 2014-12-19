#ifndef CITY_HPP_
#define CITY_HPP_

#include <string>
#include <time>

class City{
	
	std::string name;
	std::time_t time;
	unsigned int nbPlayer;
	unsigned int maxSpawn;

	public:
		City() = default;
		void addVisitor();
		void generateVisitor();
};

#endif // CITY_HPP_

