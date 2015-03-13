#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "../common/lib/Catalog.hpp"
#include "Timer.hpp"
#include <iostream>
#include "../common/lib/Map.hpp"
#include "../common/lib/Visitor.hpp"
//#include "../common/lib/Player.hpp"

// ========================================= Dijkstra ===================================
#include <iostream>
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
	public:
        CityUpdater(Map<Field>*,std::vector<Player*>*);
        void run() override;
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();
        void createPath(Location start, Location end, std::vector<Location> &path);
        void sendUpdateToPlayers(SocketMessage);
    private:
    void DijkstraComputePaths(vertex_t source, \
                          const adjacency_list_t &adjacency_list, \
                          std::vector<weight_t> &min_distance, \
                          std::vector<vertex_t> &previous);
    std::vector<vertex_t> DijkstraGetShortestPathTo( \
                        vertex_t vertex, const std::vector<vertex_t> &previous);
        int findRoad(Location);
        void getRoadMap();
        void getAdjacencyList();
};

#endif // CITYUPDATER_HPP_

