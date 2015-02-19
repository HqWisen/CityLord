#ifndef ROAD_HPP_
#define ROAD_HPP_

#include "Case.hpp"

using namespace std;

class Road : public Case{
	bool path[4] = {false};
	string image;

	public:
		Road(Location);
		~Road();
		string display();
		bool getPath(int);
		void setPath(int,bool);
};

#endif // ROAD_HPP_

