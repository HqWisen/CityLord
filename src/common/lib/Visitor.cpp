


#include "Visitor.hpp"


using namespace std;


Visitor::Visitor(){
	path = getWay();
}

Visitor::~Visitor(){

}

void Visitor::display(){

}

void Visitor::displayGUI(){

}

void Visitor::move(){

}

/*
void Visitor::enter(Building build){
	//build.receiveVisitor(this);

}
*/

std::vector<Location> Visitor::getWay(){
	std::vector<Location> way;

	return way;
}

bool Visitor::choose(){


	return true;
}
