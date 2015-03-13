#include "CityUpdater.hpp"
#include "UserManager.hpp"

// ======================================================================================
// ========================================= Dijkstra ===================================
// ======================================================================================
//      Solution temporaire (ou permanente) afin d'avoir un createPath qui marche
// ======================================================================================
void CityUpdater::DijkstraComputePaths(vertex_t source,
                          const adjacency_list_t &adjacency_list,
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
    const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
        if (distance_through_u < min_distance[v]) {
            vertex_queue.erase(std::make_pair(min_distance[v], v));
 
            min_distance[v] = distance_through_u;
            previous[v] = u;
            vertex_queue.insert(std::make_pair(min_distance[v], v));
 
        }
 
        }
    }
}
 
 
std::vector<vertex_t> CityUpdater::DijkstraGetShortestPathTo(
    vertex_t vertex, const std::vector<vertex_t> &previous)
{
    std::vector<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.insert(path.begin(), vertex);
    return path;
}

void CityUpdater::getRoadMap() {
    Location location(0,0);
    Road* road;
    for (int row=0; row<(cityMap->getNumberOfRows()); row++) {
        for (int col=0; col<(cityMap->getNumberOfCols()); col++) {
            location.setRow(row);
            location.setCol(col);
            if((road = dynamic_cast<Road*>(cityMap->getCase(location)))) {
                roadMap.push_back(road);
                if ((road->print() == "═□ ") || (road->print() == " □ ") || (road->print() == " □═")) {
                    checkPointsList.push_back(road);
                }
            }
        }
    }
}

void CityUpdater::getAdjacencyList() {
    Location location(0,0);
    Road* road;
    for (unsigned int i=0; i<roadMap.size(); i++) {
        vector<neighbor> tmpVector;
        if (roadMap[i]->isOpen(Road::NORTH) && ((roadMap[i]->getLocation().getRow())-1 >= 0)) {
            //
            location.setRow(roadMap[i]->getLocation().getRow()-1);
            location.setCol(roadMap[i]->getLocation().getCol());
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
            tmpVector.push_back(neighbor(index, 1));
            //
        }
        if (roadMap[i]->isOpen(Road::WEST) && ((roadMap[i]->getLocation().getCol())-1 >= 0)) {
            //
            location.setRow(roadMap[i]->getLocation().getRow());
            location.setCol(roadMap[i]->getLocation().getCol()-1);
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
            tmpVector.push_back(neighbor(index, 1));
            //
        }
        if (roadMap[i]->isOpen(Road::SOUTH) && ((roadMap[i]->getLocation().getRow())+1 < cityMap->getNumberOfRows())) {
            //
            location.setRow(roadMap[i]->getLocation().getRow()+1);
            location.setCol(roadMap[i]->getLocation().getCol());
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
            tmpVector.push_back(neighbor(index, 1));
            //
        }
        if (roadMap[i]->isOpen(Road::EAST) && ((roadMap[i]->getLocation().getCol())+1 < cityMap->getNumberOfCols())) {
            //
            location.setRow(roadMap[i]->getLocation().getRow());
            location.setCol(roadMap[i]->getLocation().getCol()+1);
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
            tmpVector.push_back(neighbor(index, 1));
            //
        }
        adjacencyList.push_back(tmpVector);
        tmpVector.clear();
    }
}
// ======================================================================================
// ======================================================================================
// ======================================================================================

CityUpdater::CityUpdater(Map<Field>* map,std::vector<Player*>* pvPtr){
    cityMap = map;
    spawn = map->getSpawnList();
    playerVectorPtr = pvPtr;
    getRoadMap();
    getAdjacencyList();
    this->start();
    
}

void CityUpdater::run(){
    /*
    1 seconde = 5 min dans le jeu
    */
    unsigned timer = popTimer;
    unsigned timer2 = moveTimer;
    t.start();
    while(dayRemaining!=0){
        if(t.elapsedTime() < timer2){

        }
        else{
            timer2 += moveTimer;
            makeVisitorsAdvance();
        }
        if(t.elapsedTime() < timer) {
        }
        else{
            timer += popTimer;
            updateCity();
            if(t.elapsedTime() < dayTimer){  
                 
            }
            else{   //nouveau jour
                makeOwnersPay();
                t.start();
                timer = popTimer;
                dayRemaining -= 1;
                std::cout<<"Day : "<<dayRemaining<<std::endl;
            }
        }
    }
    std::cout<<"fin du game"<<std::endl;
}

int CityUpdater::getTimeRemaining(){
    int x = dayRemaining;
    int y = t.elapsedTime();
    int minRemaining = (5*(dayTimer - y))*60;
    if(dayRemaining == 0){
        return minRemaining;
    }
    else{
        int timeRemaining = x*24*60*60;
        timeRemaining += minRemaining;
        return timeRemaining;
    }    
}

int CityUpdater::getRealTimeRemaining(){
    int y = t.elapsedTime();
    if(dayRemaining == 0){
        return dayTimer - y;
    }
    else{
        int x = dayTimer*dayRemaining;
        x += y;
        return x;
    }
}

/*
SocketMessage CityUpdater::sendTime(){
    SocketMessage update;
    update.setTopic("currentTime");
    update.set("time", getImeRemaining().toString());
    return update;
}
*/

SocketMessage CityUpdater::visitorCreate(int visitorID, Location spawnLocation){
    SocketMessage update;
    update.setTopic("visitorcreate");
    update.set("visitorid", to_string(visitorID));
    update.set("spawnlocation", spawnLocation.toString());
    return update;
}

SocketMessage CityUpdater::visitorMove(int visitorID, Location firstLocation, Location lastLocation){
    SocketMessage update;
    update.setTopic("visitormove");
    update.set("visitorid", to_string(visitorID));
    update.set("firstlocation", firstLocation.toString());
    update.set("lastlocation", lastLocation.toString());
    return update;
}

SocketMessage CityUpdater::visitorRemove(int visitorID){
    SocketMessage update;
    update.setTopic("visitorremove");
    update.set("visitorid", to_string(visitorID));
    return update;
}

void CityUpdater::sendUpdateToPlayers(SocketMessage update){
    Player* player;
    for (std::vector<Player*>::iterator it = playerVectorPtr->begin(); it != playerVectorPtr->end(); it++){
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
                    concernedField->getOwner()->loseMoney(concernedField->getBuilding()->getDailyCost());
                }
            }
        }
    }
}

void CityUpdater::createPath(Location start, Location end, std::vector<Location> &path){
    // VOIR DIJKSTRA EN HAUT !!!!
    int startIndex = std::find(roadMap.begin(), roadMap.end(), cityMap->getCase(start)) - roadMap.begin();
    int endIndex = std::find(roadMap.begin(), roadMap.end(), cityMap->getCase(end)) - roadMap.begin();
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths(startIndex, adjacencyList, min_distance, previous);
    std::vector<vertex_t> tmpPath = DijkstraGetShortestPathTo(endIndex, previous);
    for (unsigned int i=1; i<tmpPath.size(); i++){
    std::cout<<roadMap[tmpPath[i]]->getLocation().getRow()<<","<<roadMap[tmpPath[i]]->getLocation().getCol()<<std::endl;
        path.push_back(roadMap[tmpPath[i]]->getLocation());
    }
}

void CityUpdater::generateVisitors(){
    if (!cityMap->isFull()){
        int size = spawn.size();
        int luck = rand() %  (size-1);
        Spawn* startSpawn = spawn[luck];
        Location startLocation = startSpawn->getSpawnPoint();
        std::cout<<"Start "<<startLocation.getRow()<<","<<startLocation.getCol()<<std::endl;

        luck = rand() %  (size-1);
        Spawn* endSpawn = spawn[luck];
        while(endSpawn == startSpawn){
            luck = rand() %  (size-1);
            endSpawn = spawn[luck];
        }
        Location endLocation = endSpawn->getSpawnPoint();

        std::vector<Location> path;
        path.push_back(startLocation);

        Location lastLocation = startLocation;
        size = checkPointsList.size();
        if (size > 0) {
            luck = 0;
            int badLuck = 2;
            Location nextLocation;
            luck = rand() % (badLuck);
            while(luck == 0){
                luck = rand() % (size-1);
                nextLocation = checkPointsList[luck]->getLocation();
                createPath(lastLocation,nextLocation,path);
                std::cout<<"Checkpoint "<<nextLocation.getRow()<<","<<nextLocation.getCol()<<std::endl;
                lastLocation = nextLocation;
                badLuck += 1;
                luck = rand() % (badLuck);
            }
        }


        std::cout<<"End "<<endLocation.getRow()<<","<<endLocation.getCol()<<std::endl;
        createPath(lastLocation,endLocation,path);
        std::cout<<"Got Path"<<std::endl;

        Visitor* newVisitor = new Visitor(startLocation);
        std::cout<<"Taille du chemin donné :"<< path.size() <<std::endl;
        newVisitor->setPath(path);
        int id = cityMap->addVisitor(newVisitor);  
        SocketMessage update = visitorCreate(id, startLocation);
        sendUpdateToPlayers(update);
    }
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



void CityUpdater::makeVisitorsAdvance(){
    std::cout<<"Advance"<<endl;
    for(int i = 0; i < cityMap->getMaxVisitors(); i++){
        if(cityMap->getVisitor(i) != nullptr){
            Location firstLocation = cityMap->getVisitor(i)->getLoc();
            cityMap->getVisitor(i)->move();
            Location lastLocation = cityMap->getVisitor(i)->getLoc();
            SocketMessage update = visitorMove(i, firstLocation, lastLocation);
            sendUpdateToPlayers(update);
            bool enter = false;
            Building test;
            Location loc = cityMap->getVisitor(i)->getLoc();
            int col = loc.getCol();
            int row = loc.getRow();
            Location locTest(row+1,col);
            if(locTest.getRow() < cityMap->getNumberOfRows()) {
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
<<<<<<< HEAD
                                std::cout<<"ENTRE DANS BATIMENT"<<std::endl;
=======
                                SocketMessage update = visitorRemove(i);
                                sendUpdateToPlayers(update);
>>>>>>> a848249e9d235ef3cc3ea6feb70281cbbfdfcd1e
                                cityMap->deleteVisitor(i);
                                Player* owner = dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner();
                                int gain = dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome();
                                owner->gainMoney(gain);
                            }
                        }
                    }
                }
            }else {
                locTest = Location(row-1,col);
            }
            if(locTest.getRow() >= 0) {
<<<<<<< HEAD
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
                                    std::cout<<"ENTRE DANS BATIMENT"<<std::endl;
    								cityMap->deleteVisitor(i);
                                    Player* owner = dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner();
                                    int gain = dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome();
                                    owner->gainMoney(gain);
    							}
    						}
    					}
    				}
    			}
=======
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
                                    SocketMessage update = visitorRemove(i);
                                    sendUpdateToPlayers(update);
                                    cityMap->deleteVisitor(i);
                                }
                            }
                        }
                    }
                }
>>>>>>> a848249e9d235ef3cc3ea6feb70281cbbfdfcd1e
            }else {
               locTest = Location(row,col+1); 
            }
            if(locTest.getCol() < cityMap->getNumberOfCols()) {
<<<<<<< HEAD
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
                                    std::cout<<"ENTRE DANS BATIMENT"<<std::endl;
                                    cityMap->deleteVisitor(i);
                                    Player* owner = dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner();
                                    int gain = dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome();
                                    owner->gainMoney(gain);
    							}
    						}
    					}
    				}
    			}
=======
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
                                    SocketMessage update = visitorRemove(i);
                                    sendUpdateToPlayers(update);
                                    cityMap->deleteVisitor(i);
                                }
                            }
                        }
                    }
                }
>>>>>>> a848249e9d235ef3cc3ea6feb70281cbbfdfcd1e
            }else {
                locTest = Location(row,col-1);
            }
            if(locTest.getCol() >= 0) {
<<<<<<< HEAD
    			if(!enter){
    				if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
    					if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
    						enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
    						if(enter){
    							enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
    							if(enter){
                                    std::cout<<"ENTRE DANS BATIMENT"<<std::endl;
    								cityMap->deleteVisitor(i);
                                    Player* owner = dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner();
                                    int gain = dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome();
                                    owner->gainMoney(gain);
    							}
    						}
    					}
    				}
=======
                if(!enter){
                    if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
                        if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
                            enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
                            if(enter){
                                enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
                                if(enter){
                                    SocketMessage update = visitorRemove(i);
                                    sendUpdateToPlayers(update);
                                    cityMap->deleteVisitor(i);
                                }
                            }
                        }
                    }
>>>>>>> a848249e9d235ef3cc3ea6feb70281cbbfdfcd1e
                }
            }
        }
    }
}

void CityUpdater::updateCity(){
    generateVisitors();
    updateBuildings();
    std::cout<<"Fin updateCity"<<std::endl;
}



