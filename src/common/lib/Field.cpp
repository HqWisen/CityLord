#include <iostream>
#include "Field.hpp"

using namespace std;


Field::Field(Location coords){
	typeName = "Field";
	coord=coord;
	//coord.setX(coords.getX());
	//coord.setY(coords.getY());
	price=200; //default price ?
}

/*
string Field::display(){
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
*/
void Field::buildBuilding(Building* build){
	building = build;
}

//----getters & setters----
void Field::setPrice(int amount){
	price=amount;
}

int Field::getPrice(){
	return price;
}

Player* Field::getOwner(){
	return owner;
}

void Field::setOwner(Player* newOwner){
	owner = newOwner;
}

Building* Field::getBuilding(){
	return building;
}

void Field::setBuilding(Building* building){
	building=building;
}

bool Field::hasBuilding(){
	return (building != nullptr);
}
