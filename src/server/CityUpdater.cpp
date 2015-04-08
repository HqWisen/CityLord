#include "CityUpdater.hpp"
#include "UserManager.hpp"

pthread_mutex_t CityUpdater::visitormutex(PTHREAD_MUTEX_INITIALIZER);



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
    roadMap.clear();
    checkPointsList.clear();
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
    adjacencyList.clear();
    Location location(0,0);
    Road* road;
    for (unsigned int i=0; i<roadMap.size(); i++) {
        vector<neighbor> tmpVector;
        if (roadMap[i]->isOpen(Road::NORTH) && ((roadMap[i]->getLocation().getRow())-1 >= 0)) {
            //
            location.setRow(roadMap[i]->getLocation().getRow()-1);
            location.setCol(roadMap[i]->getLocation().getCol());
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            if (!(road->isBlocked())){
                int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
                tmpVector.push_back(neighbor(index, 1));
            }
            //
        }
        if (roadMap[i]->isOpen(Road::WEST) && ((roadMap[i]->getLocation().getCol())-1 >= 0)) {
            //
            location.setRow(roadMap[i]->getLocation().getRow());
            location.setCol(roadMap[i]->getLocation().getCol()-1);
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            if (!(road->isBlocked())){
                int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
                tmpVector.push_back(neighbor(index, 1));
            }
            //
        }
        if (roadMap[i]->isOpen(Road::SOUTH) && ((roadMap[i]->getLocation().getRow())+1 < cityMap->getNumberOfRows())) {
            //
            location.setRow(roadMap[i]->getLocation().getRow()+1);
            location.setCol(roadMap[i]->getLocation().getCol());
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            if (!(road->isBlocked())){
                int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
                tmpVector.push_back(neighbor(index, 1));
            }
            //
        }
        if (roadMap[i]->isOpen(Road::EAST) && ((roadMap[i]->getLocation().getCol())+1 < cityMap->getNumberOfCols())) {
            //
            location.setRow(roadMap[i]->getLocation().getRow());
            location.setCol(roadMap[i]->getLocation().getCol()+1);
            road = dynamic_cast<Road*>(cityMap->getCase(location));
            if (!(road->isBlocked())){
                int index = std::find(roadMap.begin(), roadMap.end(), road) - roadMap.begin();
                tmpVector.push_back(neighbor(index, 1));
            }
            //
        }
        adjacencyList.push_back(tmpVector);
        tmpVector.clear();
    }
}
// ======================================================================================
// ======================================================================================
// ======================================================================================

CityUpdater::CityUpdater(Map<Field>* map,std::vector<Player*>* pvPtr, Gamemode gm) : mode(gm), currentTimer(nullptr){ // : timeSender(this){
    cityMap = map;
    spawn = map->getSpawnList();
    playerVectorPtr = pvPtr;
    getRoadMap();
    getAdjacencyList();
}

void CityUpdater::run(){
    currentTimer.start();
    Timer<CityUpdater> generateTimer(this, 1), advanceTimer(this, 0), buildingTimer(this, 10), roadBlockTimer(this, 20), payTimer(this, 86400), cityTimer(this);
    generateTimer.setFunc(CityUpdater::runGenerateVisitors);
    advanceTimer.setFunc(CityUpdater::runMakeVisitorsAdvance);
    buildingTimer.setFunc(CityUpdater::runUpdateBuidlings);
    payTimer.setFunc(CityUpdater::runMakeOwnersPay);
    cityTimer.setFunc(CityUpdater::runUpdateCity);
    roadBlockTimer.setFunc(CityUpdater::runUpdateRoadBlocks);
    generateTimer.start();advanceTimer.start();buildingTimer.start();roadBlockTimer.start();payTimer.start();/*cityTimer.start();*/
    currentTimer.join();
    generateTimer.cancel();advanceTimer.cancel();buildingTimer.cancel();roadBlockTimer.cancel();payTimer.cancel();/*cityTimer.join();*/
}

void CityUpdater::runGenerateVisitors(void* object){
    pthread_mutex_lock(&visitormutex);
    //std::cout<<"generatevisitor"<<std::endl;
    void (CityUpdater::*func_ptr) (void) = &CityUpdater::generateVisitors;
    for(int i = 0;i<3;i++){
        ((static_cast<CityUpdater*>(object))->*func_ptr)();
    }
    pthread_mutex_unlock(&visitormutex);
}

void CityUpdater::runMakeVisitorsAdvance(void* object){
    pthread_mutex_lock(&visitormutex);
    //std::cout<<"advancevisitors"<<std::endl;
    void (CityUpdater::*func_ptr) (void) = &CityUpdater::makeVisitorsAdvance;
    ((static_cast<CityUpdater*>(object))->*func_ptr)();
    pthread_mutex_unlock(&visitormutex);
}

void CityUpdater::runUpdateRoadBlocks(void* object){
    pthread_mutex_lock(&visitormutex);
    //std::cout<<"updateRoadBlocks"<<std::endl;
    void (CityUpdater::*func_ptr) (void) = &CityUpdater::updateRoadBlocks;
    ((static_cast<CityUpdater*>(object))->*func_ptr)();
    pthread_mutex_unlock(&visitormutex);
}

void CityUpdater::runUpdateBuidlings(void* object){
    //std::cout<<"updatebuilding"<<std::endl;
    void (CityUpdater::*func_ptr) (void) = &CityUpdater::updateBuildings;
    ((static_cast<CityUpdater*>(object))->*func_ptr)();
}

void CityUpdater::runMakeOwnersPay(void* object){
    //std::cout<<"payowner"<<std::endl;
    void (CityUpdater::*func_ptr) (void) = &CityUpdater::makeOwnersPay;
    ((static_cast<CityUpdater*>(object))->*func_ptr)();
}

void CityUpdater::runUpdateCity(void* object){
    //std::cout<<"updatecity"<<std::endl;
    void (CityUpdater::*func_ptr) (void) = &CityUpdater::updateCity;
    ((static_cast<CityUpdater*>(object))->*func_ptr)();
}

std::string CityUpdater::getStringTimer(){
    return currentTimer.toString();
}

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
    //for (std::vector<Player*>::iterator it = playerVectorPtr->begin(); it != playerVectorPtr->end(); it++){
    for(int i = 0;i<8;i++){
        player = (*playerVectorPtr)[i];
        if(player != nullptr && player->isConnected() && player->getUserManager() != nullptr){
            if(player->getPlayerID() > 8){
                std::cout<<"PROBLEME"<<std::endl;
            }else{
                player->getUserManager()->sendUpdate(update);
            }
        }
    }
}


void CityUpdater::makeOwnersPay(){
    //std::cout<<"test nouveau jour"<<std::endl;
    Location currentLocation = Location(0, 0);
    Field* concernedField;
    for(int row=0; row<cityMap->getNumberOfRows(); row++){
        for(int col=0; col<cityMap->getNumberOfCols(); col++){
            currentLocation.setRow(row);
            currentLocation.setCol(col);
            if((concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation)))){
                if(concernedField->hasOwner() && concernedField->hasBuilding()){
                    concernedField->getOwner()->loseMoney(mode.applyDifficulty(concernedField->getBuilding()->getDailyCost()));
                }
            }
        }
    }
    //std::cout<<"cout deduit"<<std::endl;
}

void CityUpdater::refreshBuildingsList() {
    buildingsList.clear();
    Location location(0,0);
    Road* road;
    Field* field;
    for (int row=0; row<(cityMap->getNumberOfRows()); row++) {
        for (int col=0; col<(cityMap->getNumberOfCols()); col++) {
            location.setRow(row);
            location.setCol(col);
            if((field = dynamic_cast<Field*>(cityMap->getCase(location))) && field->hasBuilding()) {
                road = cityMap->findSpawnPoint(location);
                if (road != nullptr) {
                    buildingsList.push_back(road);
                }
            }
        }
    }
}

void CityUpdater::generateFullPath(Location start, Location end, std::vector<Location> &path){
    Location lastLocation = start;
    int size_buildings = buildingsList.size();
    int size_checkPoints = checkPointsList.size();

    int badLuck = 1;
    int chances = 0;
    Location nextLocation;
    int luck = rand() % (badLuck);
    while (luck >= badLuck-1) {
        if ((size_buildings-(badLuck-1)) > 0 && luck >= chances) {
            for (int i=0; i<MAXFINDATTEMPTS; i++){
                luck = rand() % (size_buildings);
                if (isRoadFree(buildingsList[luck])){
                    nextLocation = buildingsList[luck]->getLocation();
                    createPath(lastLocation,nextLocation,path);
                    //std::cout<<"Building stop "<<nextLocation.getRow()<<","<<nextLocation.getCol()<<std::endl;
                    lastLocation = nextLocation;
                    break;
                }
            }

        }
        luck = rand() % (badLuck);
        if ((size_checkPoints-(badLuck-1)) > 0 && luck <= chances) {
            for (int i=0; i<MAXFINDATTEMPTS; i++){
                luck = rand() % (size_checkPoints);
                if (isRoadFree(checkPointsList[luck])){
                    nextLocation = checkPointsList[luck]->getLocation();
                    createPath(lastLocation,nextLocation,path);
                    //std::cout<<"Checkpoint "<<nextLocation.getRow()<<","<<nextLocation.getCol()<<std::endl;
                    lastLocation = nextLocation;
                    break;
                }
            }
        }
        badLuck += 1;
        chances = (ceil((badLuck)/2))-1;
        luck = rand() % (badLuck);
    }
    createPath(lastLocation,end,path);
    //std::cout<<"Got Path"<<std::endl;
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
    //std::cout<<roadMap[tmpPath[i]]->getLocation().getRow()<<","<<roadMap[tmpPath[i]]->getLocation().getCol()<<std::endl;
        path.push_back(roadMap[tmpPath[i]]->getLocation());
    }
}

void CityUpdater::generateVisitors(){
    if (!cityMap->isFull()){
        int size = spawn.size();
        int luck = rand() %  (size);
        Spawn* startSpawn = spawn[luck];
        Location startLocation = startSpawn->getSpawnPoint();
        //std::cout<<"Start "<<startLocation.getRow()<<","<<startLocation.getCol()<<std::endl;

        luck = rand() %  (size);
        Spawn* endSpawn = spawn[luck];
        while(endSpawn == startSpawn){
            luck = rand() %  (size);
            endSpawn = spawn[luck];
        }
        Location endLocation = endSpawn->getSpawnPoint();
        //std::cout<<"End "<<endLocation.getRow()<<","<<endLocation.getCol()<<std::endl;

        std::vector<Location> path;
        generateFullPath(startLocation, endLocation, path);

        Visitor* newVisitor = new Visitor(startLocation);
        //std::cout<<"Taille du chemin donné :"<< path.size() <<std::endl;
        newVisitor->setPath(path);
        int id = cityMap->addVisitor(newVisitor);  
        SocketMessage update = visitorCreate(id, startLocation);
        sendUpdateToPlayers(update);
    }
}

bool CityUpdater::isRoadFree(Road* road){
    if (blockedRoads.size() > 0){
        for (unsigned int i=0; i<blockedRoads.size(); i++){
            if (blockedRoads[i]->getLocation().isEqual(road->getLocation())){
                return false;
            }
        }
    }
    return true;
}

bool CityUpdater::addRoadBlock(Road* toBlock){
    pthread_mutex_lock(&visitormutex);
    if (!isRoadFree(toBlock)){
        return false;
    }
    toBlock->setUpBarricade(true, MAXROADBLOCKTURNS);
    //std::cout<<"Blocking "<<toBlock->getLocation().getRow()<<" . "<<toBlock->getLocation().getCol()<<std::endl;
    blockedRoads.push_back(toBlock);
    getAdjacencyList();
    Visitor* visitorPtr;
    std::vector<Location> path;
    for (int i=0; i<cityMap->getMaxVisitors(); i++){
        if ((visitorPtr = cityMap->getVisitor(i)) && visitorPtr->passesThrough(toBlock->getLocation())){
            path.clear();
            generateFullPath(visitorPtr->getLoc(), visitorPtr->getEndLoc(), path);
            visitorPtr->setPath(path);
        }
    }
    pthread_mutex_unlock(&visitormutex);
    return true;
}

void CityUpdater::freeRoad(){
    Road* toFree = blockedRoads.front();
    //std::cout<<"Freeing "<<toFree->getLocation().getRow()<<" . "<<toFree->getLocation().getCol()<<std::endl;
    blockedRoads.pop_front();
    toFree->setUpBarricade(false);
    getAdjacencyList();
    Visitor* visitorPtr;
    std::vector<Location> path;
    for (int i=0; i<cityMap->getMaxVisitors(); i++){
        if ((visitorPtr = cityMap->getVisitor(i))){
            path.clear();
            generateFullPath(visitorPtr->getLoc(), visitorPtr->getEndLoc(), path);
            visitorPtr->setPath(path);
        }
    }
}

void CityUpdater::updateRoadBlocks(){
    if (blockedRoads.size() > 0){
        if (blockedRoads[0]->getTurnsLeft() == 0){
            SocketMessage update;
            update.setTopic("roadblock");
            update.set("location", blockedRoads[0]->getLocation().toString());
            update.set("state", "0");
            freeRoad();
            sendUpdateToPlayers(update);
        }
        if (blockedRoads.size() > 0){
            for (unsigned int i=0; i<blockedRoads.size(); i++){
                blockedRoads[i]->decreaseTurnsLeft();
            }
        }
    }
}

void CityUpdater::updateBuildings(){
    Location currentLocation;
    SocketMessage update;
    Field* concernedField;
    for(int col = 0; col < cityMap->getNumberOfCols(); col++){
        for(int row = 0; row < cityMap->getNumberOfRows(); row++){
            currentLocation = Location(row,col);
            if((concernedField = dynamic_cast<Field*>(cityMap->getCase(currentLocation)))){
                if(concernedField->hasBuilding()){
                    concernedField->getBuilding()->removeVisitor();
                    if(concernedField->getBuilding()->getStatus() == "construction"){
                        int res = concernedField->getBuilding()->getTurnToFinish();
                        if(res == 0){
                            concernedField->getBuilding()->setStatus("normal");
                            concernedField->getBuilding()->renitTurnToFinish();
                            refreshBuildingsList();
                            update.setTopic("refresh");
                            Location location(row,col);
                            update.set("location", location.toString());
                            sendUpdateToPlayers(update); 
                        }
                        else{
                            concernedField->getBuilding()->decreaseTurnToFinish();
                        }                       
                    }
                    else if(concernedField->getBuilding()->getStatus() == "destruction"){
                        int res = concernedField->getBuilding()->getTurnToFinish();
                        if(res == 0){                            
                            concernedField->destroyBuilding();  
                            refreshBuildingsList();
                            update.setTopic("destroy");
                            Location location(row,col);
                            update.set("location", location.toString());
                            sendUpdateToPlayers(update);                     
                        }
                        else{
                            concernedField->getBuilding()->decreaseTurnToFinish();
                        }              
                    }               
                }
            }
        }
    }
}

//gainMoney()

void CityUpdater::makeVisitorsAdvance(){
    //std::cout<<"Advance"<<endl;
    for(int i = 0; i < cityMap->getMaxVisitors(); i++){
        if(cityMap->getVisitor(i) != nullptr){
            if (cityMap->getVisitor(i)->hasReachedEnd()) {
                //std::cout<<"reached end "<<i<<std::endl;
                SocketMessage update = visitorRemove(i);
                sendUpdateToPlayers(update);
                cityMap->deleteVisitor(i);
            }else {
                Location firstLocation = cityMap->getVisitor(i)->getLoc();
                cityMap->getVisitor(i)->move();
                Location lastLocation = cityMap->getVisitor(i)->getLoc();
                //std::cout<<"moving "<<i<<" from to "<<lastLocation.toString()<<std::endl;
                SocketMessage update = visitorMove(i, firstLocation, lastLocation);
                sendUpdateToPlayers(update);
                bool enter = false;
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
                                    //std::cout<<"ENTREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<std::endl;
                                    dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner()->gainMoney(mode.applyAdvantage(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome()));
                                    SocketMessage update = visitorRemove(i);
                                    sendUpdateToPlayers(update);
                                    cityMap->deleteVisitor(i);
                                }
                            }
                        }
                    }
                }else {
                    locTest = Location(row-1,col);
                }
                if(locTest.getRow() >= 0) {
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
                                        //std::cout<<"ENTREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<std::endl;
                                        dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner()->gainMoney(mode.applyAdvantage(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome()));
                                        SocketMessage update = visitorRemove(i);
                                        sendUpdateToPlayers(update);
                                        cityMap->deleteVisitor(i);
                                    }
                                }
                            }
                        }
                    }
                }else {
                   locTest = Location(row,col+1); 
                }
                if(locTest.getCol() < cityMap->getNumberOfCols()) {
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
                                        //std::cout<<"ENTREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<std::endl;
                                        dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner()->gainMoney(mode.applyAdvantage(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome()));
                                        SocketMessage update = visitorRemove(i);
                                        sendUpdateToPlayers(update);
                                        cityMap->deleteVisitor(i);
                                    }
                                }
                            }
                        }
                    }
                }else {
                    locTest = Location(row,col-1);
                }
                if(locTest.getCol() >= 0) {
                    if(!enter){
                        if(dynamic_cast<Field*>(cityMap->getCase(locTest))){
                            if(dynamic_cast<Field*>(cityMap->getCase(locTest))->hasBuilding()){
                                enter = cityMap->getVisitor(i)->choose(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
                                if(enter){
                                    enter = cityMap->getVisitor(i)->enter(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding());
                                    if(enter){
                                        //std::cout<<"ENTREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<std::endl;
                                        dynamic_cast<Field*>(cityMap->getCase(locTest))->getOwner()->gainMoney(mode.applyAdvantage(dynamic_cast<Field*>(cityMap->getCase(locTest))->getBuilding()->getIncome()));
                                        SocketMessage update = visitorRemove(i);
                                        sendUpdateToPlayers(update);
                                        cityMap->deleteVisitor(i);
                                    }
                                }
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
    //std::cout<<"Fin updateCity"<<std::endl;
}



