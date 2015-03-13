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

void Visitor::setPath(std::vector<Location>* way){ 
	path = way;
}

void Visitor::move(){
	count += 1;
	//TEST
	/*
	Location test = currentLocation;
	int x = test.getRow();
	int y = test.getCol();
	std::cout<<"-----"<<std::endl;
	std::cout<<"de "<< x << "-" << y <<std::endl;
	currentLocation = path[count];
	test = currentLocation;
	x = test.getRow();
	y = test.getCol();
	std::cout<<"à "<< x << "-" << y <<std::endl;
	std::cout<<"-----"<<std::endl;
	*/
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
