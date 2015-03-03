#ifndef USERMANAGER_HPP_
#define USERMANAGER_HPP_


#include "../common/thread/Thread.hpp"
#include "CityManager.hpp"


class CityLordServer;
class CityManager;

class Generator : public Thread{

	public:
		Generator();
		void run() override;
        void generateVisitor();

};

#endif // USERMANAGER_HPP_

