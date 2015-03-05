#include "cityUpdater.hpp"

cityUpdater::cityUpdater(){
    this->start();
}

void cityUpdater::run(){
	bool stop = false;
	while(not stop){
		unsigned long timer = 10;
		Timer t;
		t.start();
		while(true){
        	if(t.elapsedTime() < timer) {
     
        	}
        	else{
                timer += 10; 
				updateCity();
			}
		}
	}
}

void cityUpdater::updateCity(){
	generateVisitors();
	updateBuildings();
	makeVisitorsAdvance();
}


void cityUpdater::generateVisitor(){
	std::cout<<"Visitor"<<std::endl;
}

void cityUpdater::updateBuildings(){

}

void cityUpdater::makeVisitorsAdvance(){
	
}