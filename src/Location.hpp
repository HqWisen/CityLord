#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <list>


class Location{
	int x, y;

public:
	Location(int,int);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
};

#endif // LOCATION_HPP_

