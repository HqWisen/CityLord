#include<iostream>
#include "Field.hpp"


using namespace std;

Field::Field(Location coords){
	this->coord=coord;
	//coord.setX(coords.getX());
	//coord.setY(coords.getY());
	price=200; //default price ?
}

void Field::display(){
	if(building){
		building->display();
	}
	else{
		cout<<" ";
	}
}

void Field::buildBuilding(Building build){
	this->building = &build;
}


//getters & setters
void Field::setPrice(int amount){price=amount;}
int Field::getPrice(){return price;}
