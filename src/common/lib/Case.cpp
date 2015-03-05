#include "Case.hpp"

//getters & setters
Location Case::getCoord(){
	return coord;
}

void Case::setCoord(Location coords){
	coord = coords;
}

string Case::getType(){
	return typeName;
}
