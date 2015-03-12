#include "CityUpdater.hpp"
#include "UserManager.hpp"

CityUpdater::CityUpdater(Map<Field>* map,std::vector<Player*> playersVector){
    cityMap = map;
    spawn = map->getSpawnList();
    this->start();
    playersList = playersVector;
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

void CityUpdater::sendUpdateToPlayers(SocketMessage update){
    Player* player;
    for (std::vector<Player*>::iterator it = playersList.begin(); it != playersList.end(); it++){
        player = *it;
        if(player->isConnected()){
            player->getUserManager()->sendUpdate(update);
        }

    }
}


void CityUpdater::makeOwnersPay(){
	std::cout<<"test nouveau jour"<<std::endl;
	Location currentLocation;
	Field* concernedField;
	for(int col = 0; col < cityMap->getNumberOfCols(); col++){
		for(int row = 0; row < cityMap->getNumberOfRows(); row++){
			currentLocation = Location(row,col);
			if((concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation)))){
				if(concernedField->hasOwner()){
					//concernedField->getOwner()->setMoney()(concernedField->getOwner()->getMoney() - concernedField->getBuilding()->dailyCost);
				}
			}
		}
    }
}

/*
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
*/

std::vector<Location>* CityUpdater::creatWay(Location start, Location end, std::vector<Location>* path){
	/*std::vector<Location>* res;
	int row = start.getRow();
	int col = start.getCol();
	std::cout<<"1"<<std::endl;
	if(start.isEqual(end)){
		std::cout<<"Fin"<<std::endl;
		res = path;}	
	else{
		Location next = Location(row,col);
		if(row+1 < cityMap->getNumberOfRows()){
			std::cout<<"2"<<std::endl;
			next.setRow(row+1);
			next.setCol(col);
			if (path->empty() or !path->back().isEqual(next)){
				std::cout<<"22"<<std::endl;
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					std::cout<<"222"<<std::endl;
					path->push_back(next);
					std::cout<<"2222"<<std::endl;
					res = creatWay(next, end, path);
					path->pop_back();
				}
			}
		}
		if(row-1 >= 0){
			std::cout<<"3"<<std::endl;
			next.setRow(row-1);
			next.setCol(col);
			if (path->empty() or !path->back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path->push_back(next);
					res = creatWay(next, end, path);
					path->pop_back();
				}
			}
		}
		if(col+1 < cityMap->getNumberOfCols()){
			std::cout<<"5"<<std::endl;
			next.setRow(row);
			next.setCol(col+1);
			if (path->empty() or !path->back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path->push_back(next);
					res = creatWay(next, end, path);
					path->pop_back();
				}
			}
		}
		if(col-1 >=0){
			std::cout<<"1"<<std::endl;
			next.setRow(row);
			next.setCol(col-1);
			if (path->empty() or !path->back().isEqual(next)){
				if(dynamic_cast<Road*>(cityMap->getCase(next))){
					path->push_back(next);
					res = creatWay(next, end, path);
					path->pop_back();
				}
			}
		}
	}
	return res;*/
}

void CityUpdater::generateVisitors(){
    /*int size = spawn.size();
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
    std::vector<Location>* path;
    std::vector<Location>* newWay = creatWay(startLocation,endLocation,path);
    std::cout<<"Got Way"<<std::endl;

    Visitor* newVisitor = new Visitor(startLocation);
    std::cout<<"Taille du chemin donné :"<< newWay->size() <<std::endl;
    newVisitor->setPath(newWay);
    cityMap->addVisitor(newVisitor);*/
}

void CityUpdater::updateBuildings(){
	std::cout<<"Update"<<endl;
    Location currentLocation;
    Field* concernedField;
	for(int col = 0; col < cityMap->getNumberOfCols(); col++){
		for(int row = 0; row < cityMap->getNumberOfRows(); row++){
			currentLocation = Location(row,col);
			if((concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation)))){
				if(concernedField->hasBuilding()){
					concernedField->getBuilding()->removeVisitor();
				}
			}
		}
    }
}

//gainMoney()

void CityUpdater::makeVisitorsAdvance(){
	std::cout<<"Advance"<<endl;
	for(int i = 0; i < cityMap->getMaxVisitors(); i++){
		if(cityMap->getVisitor(i) != nullptr){
			cityMap->getVisitor(i)->move();
			bool enter = false;
			Building test;
			Location loc = cityMap->getVisitor(i)->getLoc();
			int col = loc.getCol();
			int row = loc.getRow();
			Location locTest(row+1,col);
			if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
					enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
					if(!enter){
						locTest = Location(row-1,col);
					} else {
						enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(row-1,col);
						}
						else{
							cityMap->deleteVisitor(i);
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
					if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
						enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(row,col+1);
						} else {
							enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
							if(!enter){
								locTest = Location(row,col+1);
							} else {
								cityMap->deleteVisitor(i);
							}
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
					if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
						enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(!enter){
							locTest = Location(row,col-1);
						} else {
							enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
							if(!enter){
								locTest = Location(row,col-1);
							} else {
							cityMap->deleteVisitor(i);
							}
						}
					}
				}
			}
			if(!enter){
				if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
					if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
						enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
						if(enter){
							enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
							if(enter){
								cityMap->deleteVisitor(i);
							}
						}
					}
				}
            }
		}
	}
}

void CityUpdater::updateCity(){
	generateVisitors();
	updateBuildings();
	makeVisitorsAdvance();
	std::cout<<"Fin updateCity"<<std::endl;
}



