#include "Visitor.hpp"


Visitor::Visitor(Location loc){ //le spawner donne la localistion
	currentLocation = loc;
	int number = rand() % 4;
	preference = listOfBuildType[number];
}

Location Visitor::getLoc(){
	return currentLocation;
}

//void Visitor::displayGUI(){}

void Visitor::setPath(std::vector<Location> way){ 
	path = way;
}

void Visitor::move(){
	currentLocation.setRow(path[0].getRow());
	currentLocation.setCol(path[0].getCol());
	std::cout<<"Visitor moved to "<<path[0].getRow()<<" . "<<path[0].getCol()<<std::endl;
	path.erase(path.begin(),path.begin()+1);
}

bool Visitor::hasReachedEnd(){
	return (path.size() == 0);
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


bool Visitor::enter(Building* build){
<<<<<<< HEAD
	//if(build->addVisitor());
		//return true;
	//return false
	return true;
=======
	if(build->addVisitor());
		return true;
	return false;
>>>>>>> 3254de7673c64c106414387231052fe2836b3c56
}

bool Visitor::choose(Building* build){  //Building build en parametre
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
