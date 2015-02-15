#ifndef ROAD_HPP_
#define ROAD_HPP_

#include <string>
#include "Case.hpp"

using namespace std;

class Road : public Case{
	bool path[4] = {false};
	string image;

	public:
		Road(int, int);
		~Road();
		void display();
		bool getPath(int);
		void setPath(int,bool);
};

#endif // ROAD_HPP_

