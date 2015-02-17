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
//int-char-string ? getOwner(){return owner;};
//void setOwner(int-char-string ? owner){this.owner=owner};
