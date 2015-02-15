#ifndef ROAD_HPP_
#define ROAD_HPP_

#include <string>
#include "Case.hpp"

using namespace std;

class Road : public Case{
	Road* path[4];
	string image;

	public:
		Road(int, int);
		~Road();
		void display();
		Road* getPath(int);
		void setPath(int,Road*);
};

#endif // ROAD_HPP_

