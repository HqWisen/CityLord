#include "CityUpdater.hpp"

CityUpdater::CityUpdater(Map newMap){
	map = newMap;
    this->start();
}

void CityUpdater::makeOwnersPay(){
	/*Location currentLocation;
	for(int i = 0; i<cityMap.getDimensionX(); i++){
		for(int j = 0; i<cityMap.getDimensionY(); j++){
			currentLocation = Location(x,y);
			Field* concernedField = dynamic_cast<Field*>(cityMap.getCase(currentLocation));
			if(concernedField->hasOwner()){
				concernedField->getOwner()->setMoney()(concernedField->getOwner()->getMoney() - concernedField->getBuilding()->dailyCost);
			}
		}
	}*/
}

std::vector<Location> CityUpdater::creatWay(){
	std::vector<Location> newLoc;

	return newLoc;
}

void CityUpdater::generateVisitors(){
	std::cout<<"test"<<std::endl;
    int size = spawn.size();
    int luck = rand() %  (size-1);
    Location newLocation = spawn[luck];
    Visitor* newVisitor = new Visitor(newLocation);
    std::vector<Location> newWay = creatWay();
    newVisitor->setPath(newWay);
    //listOfVisitor.insert(newVisitor);    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void CityUpdater::updateBuildings(){
	/*Location currentLocation;
	for(int i = 0; i<cityMap.getDimensionX(); i++){
		for(int j = 0; i<cityMap.getDimensionY(); j++){
			currentLocation = Location(x,y);
			Field* concernedField = dynamic_cast<Field*>(cityMap.getCase(currentLocation));
			if(concernedField->hasBuilding()){;
				concernedField->getBuilding()->removeVisitor();
			}
		}
	}*/
}

void CityUpdater::makeVisitorsAdvance(){	
	for(unsigned i = 0; i<listOfVisitor.size(); i++){
		listOfVisitor[i]->move();
		bool enter = false;
		Building test;
		Location loc = listOfVisitor[i]->getLoc();
		int col = loc.getCol();
		int row = loc.getRow();
		Location locTest(col+1,row);
		if(typeid(map.getCase(locTest)) == typeid(test)){

		}
		else if((typeid(map.getCase(locTest)) == typeid(test)) and not enter){
			locTest.setCol(col-1);
		}		
		else if((typeid(map.getCase(locTest)) == typeid(test)) and not enter){
			locTest.setCol(col);
			locTest.setRow(row+1);
		}		
		else if((typeid(map.getCase(locTest)) == typeid(test)) and not enter){
			locTest.setCol(col);
			locTest.setRow(row-1);
		}
	}
}

void CityUpdater::updateCity(){
	generateVisitors();
	updateBuildings();
	makeVisitorsAdvance();
}

void CityUpdater::run(){
	bool stop = false;
	while(not stop){
		unsigned long timer = 10;
		Timer t;
		t.start();
		while(true){
        	if(t.elapsedTime() < timer) {
     
        	}
        	else{
                timer += 10; 
				updateCity();
				if(timer == 720){  //nouveau jour
					makeOwnersPay();
					timer = 0;
				}				
			}
		}
	}
}


