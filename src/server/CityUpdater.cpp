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

<<<<<<< HEAD
/*
std::vector<Location> CityUpdater::creatWay(Visitor* visitor, Location loc){
=======
std::vector<Location> CityUpdater::creatWay(Visitor* visitor, Location loc, Location previousLoc){
>>>>>>> 7036cb39d260a1b39850f86e30571d9b8640323d
    std::vector<Location> newLoc;	
	newLoc.push_back(loc);
	
	int row = loc.getRow();
	int col = loc.getCol();

	row += 1;
	loc.setRow(row);	
	if( (dynamic_cast<Road*>(cityMap->getCase(loc))) and row>=0 and row<cityMap->getNumberOfRows() and col>=0 and col<cityMap->getNumberOfCols()){
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
	if(dynamic_cast<Road*>(cityMap->getCase(loc)) and row>=0 and row<cityMap->getNumberOfRows() and col>=0 and col<cityMap->getNumberOfCols()){
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
	if(dynamic_cast<Road*>(cityMap->getCase(loc)) and row>=0 and row<cityMap->getNumberOfRows() and col>=0 and col<cityMap->getNumberOfCols()){
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
	if(dynamic_cast<Road*>(cityMap->getCase(loc)) and row>=0 and row<cityMap->getNumberOfRows() and col>=0 and col<cityMap->getNumberOfCols()){
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
*/

std::vector<Location> CityUpdater::creatWay(Location start, Location end, std::vector<Location> path){
	std::vector<Location> res;
	int row = start.getRow();
	int col = start.getCol();
	if(start.isEqual(end)){res= path;}
	else{
		Location next = Location(row,col);
		if(row+1 < cityMap->getNumberOfRows()){
			next.setRow(row+1);
			next.setCol(col);
			if (path.empty() or !path.back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path.push_back(next);
					res = creatWay(next, end, path);
					path.pop_back();
				}
			}
		}
		if(row-1 >= 0){
			next.setRow(row-1);
			next.setCol(col);
			if (path.empty() or !path.back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path.push_back(next);
					res = creatWay(next, end, path);
					path.pop_back();
				}
			}
		}
		if(col+1 < cityMap->getNumberOfCols()){
			next.setRow(row);
			next.setCol(col+1);
			if (path.empty() or !path.back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path.push_back(next);
					res = creatWay(next, end, path);
					path.pop_back();
				}
			}
		}
		if(col-1 >=0){
			next.setRow(row);
			next.setCol(col-1);
			if (path.empty() or !path.back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path.push_back(next);
					res = creatWay(next, end, path);
					path.pop_back();
				}
			}
		}
	}
	return res;
}

void CityUpdater::generateVisitors(){
    int size = spawn.size();
    std::cout<<"Taille de la liste de spawn :"<< spawn.size() <<std::endl;
    int luck = rand() %  (size-1);
    Spawn* startSpawn = spawn[luck];
    Location startLocation = startSpawn->getSpawnPoint();
	std::cout<<"First Spawn"<<std::endl;
    luck = rand() %  (size-1);
    Spawn* endSpawn = spawn[luck];
    while(endSpawn==startSpawn){
    	luck = rand() %  (size-1);
    	endSpawn = spawn[luck];
    }
    Location endLocation = endSpawn->getSpawnPoint();
    std::cout<<"Second Spawn"<<std::endl;
    
    //std::vector<Location> newWay = creatWay(newVisitor, startLocation);
    std::vector<Location> path;
    std::vector<Location> newWay = creatWay(startLocation,endLocation,path);
    std::cout<<"Got Way"<<std::endl;

    Visitor* newVisitor = new Visitor(startLocation);
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
			
			if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
				enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
				if(!enter){
					locTest = Location(col-1,row);
				} else {
					enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
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



