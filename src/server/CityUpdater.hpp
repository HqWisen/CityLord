#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Catalog.hpp"
#include "Gamemode.hpp"
#include <iostream>
#include "../common/models/Map.hpp"
#include "Visitor.hpp"
#include "../common/models/Timer.hpp"
#include <cmath>
#include <deque>

// ========================================= Dijkstra ===================================
#include <vector>
#include <string>
 
#include <limits> // for numeric_limits
 
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

#include <sstream>
#include <iostream>
#include <iomanip>
 
typedef int vertex_t;
typedef double weight_t;
 
const weight_t max_weight = std::numeric_limits<double>::infinity();
const int MAXFINDATTEMPTS = 3;
const int MAXROADBLOCKTURNS = 6;
 
struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
 
typedef std::vector<std::vector<neighbor> > adjacency_list_t;
// ======================================================================================

class CityUpdater : public Thread{

    Gamemode mode;
    Map<Field>* cityMap;
    std::vector<Spawn*> spawn;
    std::vector<Player*>* playerVectorPtr;
    vector<Road*> checkPointsList;
    vector<Road*> buildingsList;
    vector<Road*> roadMap;
    deque<Road*> blockedRoads;
    adjacency_list_t adjacencyList;
    Timer<CityUpdater> currentTimer;
    public:
        static pthread_mutex_t visitormutex;
    public:
        CityUpdater(Map<Field>*,std::vector<Player*>*, Gamemode);
        void run() override;
        static void runGenerateVisitors(void*);
        static void runMakeVisitorsAdvance(void*);
        static void runUpdateBuidlings(void*);
        static void runUpdateRoadBlocks(void*);
        static void runMakeOwnersPay(void*);
        static void runUpdateCity(void*);
        std::string getStringTimer();
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();
        void generateFullPath(Location start, Location end, std::vector<Location> &path);
        void createPath(Location start, Location end, std::vector<Location> &path);
		bool isRoadFree(Road*);
        bool addRoadBlock(Road*);
		void freeRoad();
        void updateRoadBlocks();
        SocketMessage visitorCreate(int, Location);
        SocketMessage visitorMove(int, Location, Location);
        SocketMessage visitorRemove(int);
        void sendUpdateToPlayers(SocketMessage);
        std::string getRealTimeRemaining();
        SocketMessage sendTime();
        bool getNight();
        void refreshBuildingsList();
    private:
        void DijkstraComputePaths(vertex_t source, \
                          const adjacency_list_t &adjacency_list, \
                          std::vector<weight_t> &min_distance, \
                          std::vector<vertex_t> &previous);
        std::vector<vertex_t> DijkstraGetShortestPathTo( \
                        vertex_t vertex, const std::vector<vertex_t> &previous);
        void getRoadMap();
        void getAdjacencyList();
};

#endif // CITYUPDATER_HPP_

