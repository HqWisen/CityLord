#include <iostream>
#include "Obstacle.hpp"

using namespace std;

Obstacle::Obstacle(Location coords){
	typeName = "Obstacle";
	coord = coords;
}

Obstacle::~Obstacle(){
	typeName = "";
}

string Obstacle::display(){
	return " ♦ ";
}