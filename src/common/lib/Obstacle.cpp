#include <iostream>
#include "Obstacle.hpp"

using namespace std;

void Obstacle::Obstacle(int x, int y){
	typeName = "Obstacle";
	coord = Location(x, y);
}

void Obstacle::display(){
	cout<<" ♦ ";
}