#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <string>

class Location{
	int x, y;

	public:
		Location();						//Constructeur par défaut
		Location(int,int);				//Constructeur	
		Location(const Location&);		//Constructeur de copie
		Location& operator=(const Location&);		//opérateur d'affectation
		~Location();
		int getX();
		int getY();
		void setX(int);
		void setY(int);
		std::string toString();

};

#endif // LOCATION_HPP_

