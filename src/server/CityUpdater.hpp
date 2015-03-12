#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "../common/lib/Catalog.hpp"
#include "Timer.hpp"
#include <iostream>
#include "../common/lib/Map.hpp"
#include "../common/lib/Visitor.hpp"


class CityUpdater : public Thread{
    Map<Field>* cityMap;
    std::vector<Spawn*> spawn;
    std::vector<Player*> playersList;
	public:
        CityUpdater(Map<Field>*,std::vector<Player*>);
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

