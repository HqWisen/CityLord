#include "Case.hpp"

//getters & setters
Location Case::getCoord(){
	return coord;
}

void Case::setCoord(int x, int y){
	coord.setX(x); coord.setY(y);
}

