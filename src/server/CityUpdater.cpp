#include "CityUpdater.hpp"

CityUpdater::CityUpdater(Map<Field>* map){
    cityMap = map;
    spawn = map->getSpawnList();
    this->start();
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
                if(timer == 20){  //nouveau jour
                    makeOwnersPay();
                    timer = 0;
                }
            }
        }
    }
}



void CityUpdater::makeOwnersPay(){
<<<<<<< HEAD
	std::cout<<"test Make Owner"<<std::endl;
	/*
	Location currentLocation;
	for(int i = 0; i < 10 ; i++){ //cityMap->getDimensionX()
		for(int j = 0; i < 10; j++){ //cityMap->getDimensionX()
			currentLocation = Location(i,j);
=======
	/*Location currentLocation;
	for(int col = 0; col<cityMap->getCol(); col++){
		for(int row = 0; row<cityMap->getRow(); row++){
			currentLocation = Location(col,row);
>>>>>>> c2030fae2e5947bb6641f4beb2fe8d509489b7ef
			Field* concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation));
			if(concernedField->hasOwner()){
				//concernedField->getOwner()->setMoney()(concernedField->getOwner()->getMoney() - concernedField->getBuilding()->dailyCost);
			}
		}
    }
    */

}

std::vector<Location> CityUpdater::creatWay(Visitor* visitor){
    std::vector<Location> newLoc;
	Location previousLoc = visitor->getLoc();
	newLoc.push_back(previousLoc);
	bool end = false;
	bool goOut = false;
	bool goBack = false;
	while(!end and !goOut){
        end = true;
	}
    return newLoc;
	
}

void CityUpdater::generateVisitors(){
    int size = spawn.size();
    int luck = rand() %  (size-1);
    Spawn* newSpawn = spawn[luck];
    Location newLocation = newSpawn->getSpawnPoint();
    Visitor* newVisitor = new Visitor(newLocation);
    std::vector<Location> newWay = creatWay(newVisitor);
    newVisitor->setPath(newWay);
    cityMap->addVisitor(newVisitor);
}

void CityUpdater::updateBuildings(){
    /*Location currentLocation;
	for(int col = 0; col<cityMap->getCol(); col++){
		for(int row = 0; row<cityMap->getRow(); row++){
			currentLocation = Location(col,row);
			Field* concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation));
			if(concernedField->hasBuilding()){;
				concernedField->getBuilding()->removeVisitor();
			}
		}
    }*/

}

void CityUpdater::makeVisitorsAdvance(){	

	for(int i = 0; i < cityMap->getMaxVisitors(); i++){
		if(cityMap->getVisitor(i) != nullptr){
			cityMap->getVisitor(i)->move();
			bool enter = false;
			Building test;
			Location loc = cityMap->getVisitor(i)->getLoc();
			int col = loc.getCol();
			int row = loc.getRow();
			Location locTest(col+1,row);
			/*
			Utilise la fonction choose de visitor pour voir si il rentre dans le batiment
			if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
				enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
				if(!enter){
					locTest = Location(col-1,row);
				} else {
					enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap.getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(col-1,row);
					}
					else{
						cityMap->deleteVisitor(i);
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
					enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(col,row+1);
					} else {
						enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(col,row+1);
						} else {
							cityMap->deleteVisitor(i);
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
					enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(col,row-1);
					} else {
						enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(col,row-1);
						} else {
							cityMap->deleteVisitor(i);
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
					enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
					if(enter){
						enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(enter){
							cityMap->deleteVisitor(i);
					}
				}
            }*/
		}
	}
}

void CityUpdater::updateCity(){
	generateVisitors();
	updateBuildings();
	makeVisitorsAdvance();
	std::cout<<"Fin updateCity"<<std::endl;
}



