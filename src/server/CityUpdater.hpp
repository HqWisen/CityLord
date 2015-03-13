#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Catalog.hpp"
#include "Timer.hpp"
#include <iostream>
#include "../common/models/Map.hpp"
#include "../common/models/Visitor.hpp"

// ========================================= Dijkstra ===================================
#include <vector>
#include <string>
 
#include <limits> // for numeric_limits
 
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

 
typedef int vertex_t;
typedef double weight_t;
 
const weight_t max_weight = std::numeric_limits<double>::infinity();
 
struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
 
typedef std::vector<std::vector<neighbor> > adjacency_list_t;
// ======================================================================================

class CityUpdater : public Thread{
    Map<Field>* cityMap;
    std::vector<Spawn*> spawn;
    std::vector<Player*>* playerVectorPtr;
    vector<Road*> checkPointsList;
    vector<Road*> roadMap;
    adjacency_list_t adjacencyList;
    Timer t;
    unsigned moveTimer = 1;
    unsigned dayRemaining = 3;
    unsigned popTimer = 8;
    unsigned dayTimer = 288;
    bool night = false;
    public:
        CityUpdater(Map<Field>*,std::vector<Player*>*);
        void run() override;
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();
        void createPath(Location start, Location end, std::vector<Location> &path);
        SocketMessage visitorCreate(int, Location);
        SocketMessage visitorMove(int, Location, Location);
        SocketMessage visitorRemove(int);
        void sendUpdateToPlayers(SocketMessage);
        int getTimeRemaining();
        int getRealTimeRemaining();
        //SocketMessage sendTime();
        bool getNight();
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

