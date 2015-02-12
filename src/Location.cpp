#include "Location.hpp"

Location::Location(int a,int b){
	x=a; y=b;
}

//getters & setters
int Location::getX(){return x;}
int Location::getY(){return y;}
void Location::setX(int a){x=a;}
void Location::setY(int b){y=b;}