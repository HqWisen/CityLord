#ifndef CITYUPDATER_HPP_
#define CITYUPDATER_HPP_


#include "../common/thread/Thread.hpp"
#include "Timer.hpp"
#include <iostream>



class cityUpdater : public Thread{

	public:
		cityUpdater();
		void run() override;
        void generateVisitor();

};

#endif // CITYUPDATER_HPP_

