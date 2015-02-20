#include "Case.hpp"

//getters & setters
Location Case::getCoord(){
	return coord;
}

void Case::setCoord(Location coords){
	coord = coords;
}

bool Case::isField(){
	return false;
}

string Case::getType(){
	return typeName;
}
