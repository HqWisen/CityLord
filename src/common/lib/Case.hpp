#ifndef CASE_HPP_
#define CASE_HPP_

#include <string>
#include "Location.hpp"

using namespace std;

class Case{
	protected:
		string typeName = "";
		Location coord;

	public:
		virtual void display();	//Pure virtuelle, fait de Case une classe abstraite
		Location getCoord();
		void setCoord(int,int);
		string getType();
};

#endif // CASE_HPP_