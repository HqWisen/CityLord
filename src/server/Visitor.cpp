#include "Visitor.hpp"


Visitor::Visitor(Location loc){ //le spawner donne la localistion
	currentLocation = loc;
	int number = rand() % 4;
	preference = listOfBuildType[number];
}

Location Visitor::getLoc(){
	return currentLocation;
}

Location Visitor::getEndLoc(){
	return path[path.size()-1];
}

//void Visitor::displayGUI(){}

void Visitor::setPath(std::vector<Location> way){
	path.clear();
	path = way;
}

bool Visitor::passesThrough(Location location){
	for (unsigned int i=0; i<path.size(); i++){
		if ((path[i].getRow() == location.getRow()) && (path[i].getCol() == location.getCol())){
			return true;
		}
	}
	return false;
}

void Visitor::move(){
	if (path.size() > 0 && !onStandby){
		currentLocation.setRow(path[0].getRow());
		currentLocation.setCol(path[0].getCol());
		path.erase(path.begin(),path.begin()+1);
        //std::cout<<"Visitor moved to "<<currentLocation.getRow()<<" . "<<currentLocation.getCol()<<std::endl;
	}
}

bool Visitor::hasReachedEnd(){
	return (path.size() == 0 && !onStandby);
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
	//if(build->addVisitor());
		//return true;
	//return false
	return true;
	/*
	if(build->addVisitor());
		return true;
	return false;
	*/

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

void Visitor::setOnStandby(bool bin){
	onStandby = bin;
}

bool Visitor::isOnStandby(){
	return onStandby;
}
