#include "Location.hpp"

Location::Location(){
	x=0; y=0;
}

Location::Location(int a,int b){
	x=a; y=b;
}

Location::Location(const Location  &s){
	this->x=s.x; this->y=s.y;
}

Location& Location::operator=(const Location &s){
	this->x=s.x; this->y=s.y;
	return *this;
}

Location::~Location(){
	this->x=0; this->y=0;
}

//getters & setters
int Location::getX(){
	return x;
}

int Location::getY(){
	return y;
}

void Location::setX(int a){
	x=a;
}

void Location::setY(int b){
	y=b;
}