#include <iostream>
#include "Obstacle.hpp"

using namespace std;

Obstacle::Obstacle(int x, int y){
	typeName = "Obstacle";
	coord = Location(x, y);
}

Obstacle::~Obstacle(){
	typeName = "";
}

void Obstacle::display(){
	cout<<" ♦ ";
}