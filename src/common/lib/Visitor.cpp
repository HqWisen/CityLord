#include "Visitor.hpp"


Visitor::Visitor(Location loc){ //le spawner donne la localistion
	currentLocation = loc;
	path = getWay();
	int number = rand() % 4;
	preference = listOfBuildType[number];
}

Visitor::~Visitor(){

}

void Visitor::displayGUI(){

}

void Visitor::move(){
	bool end = false;
	unsigned timeWait = 1;
	while( ! end){
		sleep(timeWait);
		end= true;
	}
}

void Visitor::moveGUI(){
	bool end = false;
	unsigned timeWait = 1;
	while( ! end){
		sleep(timeWait);
		end = true;
	}
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
