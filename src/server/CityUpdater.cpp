#include "CityUpdater.hpp"

CityUpdater::CityUpdater(Map<Field>* map){
    cityMap = map;
    spawn = map->getSpawnList();
    this->start();
    //std::cout<<"testeuh"<<std::endl;
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

std::vector<Location> CityUpdater::creatWay(Visitor* visitor){
    std::vector<Location> newLoc;
	Location previousLoc = visitor->getLoc();
	//newLoc.insert(visitor->getLoc());
	bool end = false;
	bool enter = false;
	//bool goBack = false;
	while(!end and !enter){
        end = true;
	}
    return newLoc;
	
}

void CityUpdater::generateVisitors(){
	std::cout<<"1"<<std::endl;
    int size = spawn.size();
    std::cout<<"2"<<std::endl;
    int luck = rand() %  (size-1);
    std::cout<<"3"<<std::endl;
    Spawn* newSpawn = spawn[luck];
    std::cout<<"4"<<std::endl;
    Location newLocation = newSpawn->getSpawnPoint();
    Visitor* newVisitor = new Visitor(newLocation);
    std::cout<<"5"<<std::endl;
    std::vector<Location> newWay = creatWay(newVisitor);
    std::cout<<"6"<<std::endl;
    newVisitor->setPath(newWay);
    std::cout<<"7"<<std::endl;
    cityMap->addVisitor(newVisitor);
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
<<<<<<< HEAD
	for(int i = 0; i < map.getMaxVisitors(); i++){
		if(map->getVisitor(i) != nullptr){
			map->getVisitor(i)->move();
			bool enter = false;
			Building test;
			Location loc = map->getVisitor(i)->getLoc();
=======
	for(int i = 0; i < cityMap->getMaxVisitors(); i++){
		if(cityMap->getVisitor(i) != nullptr){
			cityMap->getVisitor(i)->move();
			bool enter = false;
			Building test;
			Location loc = cityMap->getVisitor(i)->getLoc();
>>>>>>> 62ef8da56d7f2e763ba972f666e1cf316a7ad119
			int col = loc.getCol();
			int row = loc.getRow();
			Location locTest(col+1,row);
			/*
			Utilise la fonction choose de visitor pour voir si il rentre dans le batiment
			if(dynamic_cast<Field*>(map->getCase(locTest))->hasBuilding()){
				enter = map->getVisitor(i)->choose(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
				if(!enter){
					locTest = Location(col-1,row);
				} else {
					enter = map->getVisitor(i)->enter(dynamic_cast<Field*>(map.getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(col-1,row);
					}
					else{
						map->deleteVisitor(i);
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(map->getCase(locTest))->hasBuilding()){
					enter = map->getVisitor(i)->choose(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(col,row+1);
					} else {
						enter = map->getVisitor(i)->enter(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(col,row+1);
						} else {
							map->deleteVisitor(i);
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(map->getCase(locTest))->hasBuilding()){
					enter = map->getVisitor(i)->choose(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(col,row-1);
					} else {
						enter = map->getVisitor(i)->enter(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(col,row-1);
						} else {
							map->deleteVisitor(i);
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(map->getCase(locTest))->hasBuilding()){
					enter = map.getVisitor(i)->choose(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
					if(enter){
						enter = map->getVisitor(i)->enter(dynamic_cast<Field*>(map->getCase(locTest))->getBuilding());
						if(enter){
							map->deleteVisitor(i);
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



