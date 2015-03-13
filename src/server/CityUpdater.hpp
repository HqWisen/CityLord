#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Catalog.hpp"
#include "Timer.hpp"
#include <iostream>
#include "../common/models/Map.hpp"
#include "../common/models/Visitor.hpp"

class CityUpdater : public Thread{
    Map<Field>* cityMap;
    std::vector<Spawn*> spawn;
    std::vector<Player*>* playerVectorPtr;
	public:
        CityUpdater(Map<Field>*,std::vector<Player*>*);
        void run() override;
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();
        //std::vector<Location> creatWay(Visitor*, Location);
        std::vector<Location>* creatWay(Location,Location,std::vector<Location>*);
        void sendUpdateToPlayers(SocketMessage);

};

#endif // CITYUPDATER_HPP_

