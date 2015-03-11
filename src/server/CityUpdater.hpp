#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <iostream>
#include "../common/lib/Map.hpp"
#include "../common/lib/Visitor.hpp"


class CityUpdater : public Thread{
    Map<Field>* map;
    std::vector<Spawn*> spawn;
	public:
        CityUpdater(Map<Field>*);
        void run() override;
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();
        std::vector<Location> creatWay(Visitor*);

};

#endif // CITYUPDATER_HPP_

