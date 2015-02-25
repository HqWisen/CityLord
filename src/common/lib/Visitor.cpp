#include "Visitor.hpp"


Visitor::Visitor(Location loc){ //le spawner donne la localistion
	currentLocation = loc;
	path = getWay();
	int number = rand() % 4;
	preference = listOfBuildType[number];
}

/*
Visitor::~Visitor(){}
*/

void Visitor::displayGUI(){

}

void Visitor::move(){
	bool end = false;
	unsigned timeWait = 1;
	unsigned count = 0;

	while( ! end){
		count += 1;
		
		if(count-1 > path.size()){
			end = true;
			delete this;
		}
		
		currentLocation = path[count];
		sleep(timeWait);
		bool test = choose(); //Building en parametre

		if(test){
			end = true;
			delete this;
		}
	}
}

void Visitor::moveGUI(){
	bool end = false;
	unsigned timeWait = 1;
	unsigned count = 0;

	while( ! end){
		count += 1;
		
		if(count-1 > path.size()){
			end = true;
			delete this;
		}

		else{
			currentLocation = path[count];

			this->displayGUI();

			sleep(timeWait);
			bool test = choose(); //Building en parametre

			if(test){
				end = true;
				delete this;
			}
		}
	}
}

/*
void Visitor::enter(Building build){
	//build.receiveVisitor(this);

}
*/

std::vector<Location> Visitor::getWay(){
	std::vector<Location> way;



	return way;
}

bool Visitor::choose(){  //Building en parametre



	return true;
}
