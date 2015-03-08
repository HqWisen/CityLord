#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <iostream>
#include "../common/lib/Map.hpp"
#include "../common/lib/Visitor.hpp"

/*
class CityUpdater : public Thread{
	Map map;
	std::vector<Location> spawn;  //=map.getListSpawn
	std::vector<Visitor*> listOfVisitor;
	public:
		CityUpdater(Map);
		void run() override;
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();
        std::vector<Location> creatWay();

};
*/
#endif // CITYUPDATER_HPP_

