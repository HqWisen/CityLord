#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <iostream>



class CityUpdater : public Thread{

	public:
		CityUpdater();
		void run() override;
        void generateVisitors();
        void updateBuildings();
        void makeVisitorsAdvance();
        void makeOwnersPay();
        void updateCity();

};

#endif // CITYUPDATER_HPP_

