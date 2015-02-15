#ifndef CASE_HPP_
#define CASE_HPP_

#include "Location.hpp"

class Case{
protected:
	Location coord;

public:
	virtual void display();	//Pure virtuelle, fait de Case une classe abstraite
	Location getCoord();
	void setCoord(int,int);
};

#endif // CASE_HPP_