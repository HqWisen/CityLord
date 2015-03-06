#include "Obstacle.hpp"

using namespace std;

Obstacle::Obstacle(Location location) : Case(location){
}

std::string Obstacle::print(){
	return " ♦ ";
}
