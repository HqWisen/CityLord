#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <list>


class Location{
	int x, y;

public:
	Location();						//Constructeur par défaut
	Location(int,int);				//Constructeur	
	Location(const Location&);		//Constructeur de copie
	Location& operator=(const Location&);		//opérateur d'affectation
	int getX();
	int getY();
	void setX(int);
	void setY(int);

};

#endif // LOCATION_HPP_

