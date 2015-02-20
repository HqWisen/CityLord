#include <iostream>
#include "Obstacle.hpp"

using namespace std;

Obstacle::Obstacle(Location coords){
	typeName = "Obstacle";
	coord = coords;
}

string Obstacle::display(){
	return " ♦ ";
}
