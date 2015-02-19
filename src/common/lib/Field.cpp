#include <iostream>
#include <string>

#include "Field.hpp"

using namespace std;


Field::Field(Location coords){
	this->coord=coord;
	//coord.setX(coords.getX());
	//coord.setY(coords.getY());
	price=200; //default price ?
}
/*
void Field::display(){
	string color;
	if(this->asOwner()){
		color=this->owner.getColor();
	}
	else{color="\033[0m";}

	if(building){
		cout<<color<<" B \033[0m\n";
		//building->display();
	}
	else{
		cout<<color<<"   \033[0m\n";
	}
}

void Field::buildBuilding(Building build){
	this->building = &build;
}
*/

//----getters & setters----
void Field::setPrice(int amount){price=amount;}
int Field::getPrice(){return price;}
//Player Field::getOwner(){return owner;};
//void Field::setOwner(Player owner){this.owner=owner};
Building* Field::getBuilding(){return building;}
void Field::setBuilding(Building* building){this->building=building;}
bool Field::hasBuilding(){return building!=NULL;}