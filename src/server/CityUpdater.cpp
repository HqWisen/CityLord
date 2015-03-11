#include "CityUpdater.hpp"

CityUpdater::CityUpdater(Map<Field>* map){
    cityMap = map;
    spawn = map->getSpawnList();
    this->start();
}

void CityUpdater::run(){
    bool stop = false;
    unsigned long timer = 10;
    Timer t;
    t.start();
    while(not stop){ 
        while(true){
            if(t.elapsedTime() < timer) {
            }
            else{
                timer += 10;
                updateCity();
                if(t.elapsedTime() < 20){  //nouveau jour
                    
                }
                else{
                	makeOwnersPay();
                    t.start();
                    timer = 10;
                }
            }
        }
    }
}



void CityUpdater::makeOwnersPay(){
	std::cout<<"test nouveau jour"<<std::endl;
	/*
	Location currentLocation;
	for(int i = 0; i < 10 ; i++){ //cityMap->getDimensionX()
		for(int j = 0; i < 10; j++){ //cityMap->getDimensionX()
			currentLocation = Location(i,j);
=======
	Location currentLocation;
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

std::vector<Location> CityUpdater::creatWay(Visitor* visitor, Location loc){
    std::vector<Location> newLoc;	
	newLoc.push_back(loc);
	
	int row = loc.getRow();
	int col = loc.getCol();

	row += 1;
	loc.setRow(row);	
	if(dynamic_cast<Road*>(cityMap->getCase(loc))){
		std::cout<<"1"<<std::endl;
		std::vector<Location> newAdd = creatWay(visitor ,loc);
		unsigned count = 0;
		for(unsigned i=0; i < newAdd.size(); i++){
			newLoc.push_back(newAdd[i]);
			count += 1;
		}
		for(unsigned i=0; i < count; i++){
			newLoc.pop_back();
		}
	}

	row -= 2;
	loc.setRow(row);	
	if(dynamic_cast<Road*>(cityMap->getCase(loc))){
		std::cout<<"2"<<std::endl;
		std::vector<Location> newAdd = creatWay(visitor ,loc);
		unsigned count = 0;
		for(unsigned i=0; i < newAdd.size(); i++){
			newLoc.push_back(newAdd[i]);
			count += 1;
		}
		for(unsigned i=0; i < count; i++){
			newLoc.pop_back();
		}	
	}

	row += 1;
	loc.setRow(row);
	col +=1;
	loc.setCol(col);	
	if(dynamic_cast<Road*>(cityMap->getCase(loc))){
		std::cout<<"3"<<std::endl;
		std::vector<Location> newAdd = creatWay(visitor ,loc);
		unsigned count = 0;
		for(unsigned i=0; i < newAdd.size(); i++){
			newLoc.push_back(newAdd[i]);
			count += 1;
		}
		for(unsigned i=0; i < count; i++){
			newLoc.pop_back();
		}
	}

	col-=2;
	loc.setCol(col);	
	if(dynamic_cast<Road*>(cityMap->getCase(loc))){
		std::cout<<"4"<<std::endl;
		std::vector<Location> newAdd = creatWay(visitor ,loc);
		unsigned count = 0;
		for(unsigned i=0; i < newAdd.size(); i++){
			newLoc.push_back(newAdd[i]);
			count += 1;
		}
		for(unsigned i=0; i < count; i++){
			newLoc.pop_back();
		}	
	}

    return newLoc;	
}

void CityUpdater::generateVisitors(){
    int size = spawn.size();
    std::cout<<"Taille de la liste de spawn :"<< spawn.size() <<std::endl;
    int luck = rand() %  (size-1);
    Spawn* newSpawn = spawn[luck];
    Location newLocation = newSpawn->getSpawnPoint();
    Visitor* newVisitor = new Visitor(newLocation);
    std::vector<Location> newWay = creatWay(newVisitor, newLocation);
    std::cout<<"Taille du chemin donné :"<< newWay.size() <<std::endl;
    newVisitor->setPath(newWay);
    cityMap->addVisitor(newVisitor);
}

void CityUpdater::updateBuildings(){
	/*
    Location currentLocation;
	for(int col = 0; col < cityMap->getNumberOfCols(); col++){
		for(int row = 0; row < cityMap->getNumberOfRows(); row++){
			currentLocation = Location(col,row);
			Field* concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation));
			if(concernedField->hasBuilding()){;
				concernedField->getBuilding()->removeVisitor();
			}
		}
    }
    */
}

//gainMoney()

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



