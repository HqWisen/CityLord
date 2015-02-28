#include "Visitor.hpp"


Visitor::Visitor(Location loc){ //le spawner donne la localistion
	currentLocation = loc;
	//path = getWay();
	int number = rand() % 4;
	preference = listOfBuildType[number];
}

/*
Visitor::~Visitor(){}
*/

void Visitor::displayGUI(){}

void Visitor::move(){
	bool end = false;
	count += 1;
		
	if(count-1 > path.size()){
		end = true;
		delete this;
	}
	else{		
		currentLocation = path[count];
		//int x = currentLocation.getX();
		//int y = currentLocation.getY();
		if(end){  // map[x][y]  avec +1 -1
			bool test = choose(); //Building en parametre
			if(test){
				end = true;
				//enter(build);
				delete this;
			}
		}
	}
}


/*
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
			bool test = choose(); //Building en parametre
			if(test){
				end = true;
				delete this;
			}
		}
	}
}
*/


void Visitor::enter(Building build){
	//if build.addVisitor();
		//ok
	//else....

}

bool Visitor::choose(){  //Building build en parametre
	if(true){   //preference = build.getType
		int luck = rand() %  10 + 1;
		if(luck <= 6){  
			return true;   // 60% de chance de rentrer dans le batiment
		}
	}
	else{
		int luck = rand() %  10 + 1;
		if(luck <= 2){
			return true;   // 20% de chance de rentrer dans le batiment
		}		
	}
	return false;  // ne rentre pas dans le batiment
}
