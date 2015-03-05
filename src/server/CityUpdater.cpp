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
	/*Location currentLocation;
	for(int i = 0; i<cityMap.getDimensionX(); i++){
		for(int j = 0; i<cityMap.getDimensionY(); j++){
			currentLocation = Location(x,y);
			Field* concernedField = dynamic_cast<Field*>(cityMap.getCase(currentLocation))
			if(concernedField->hasBuilding()){;
				//Faire sortir les visiteurs du building, puis faire payer le joueur
			}
		}
	}*/
}

void cityUpdater::makeVisitorsAdvance(){
	/*Location currentLocation;
	for(int i = 0; i<cityMap.getDimensionX(); i++){
		for(int j = 0; i<cityMap.getDimensionY(); j++){
			currentLocation = Location(x,y);
			Case* concernedCase = cityMap.getCase(currentLocation)
			if(concernedCase->hasVisitors()){
				for(k = 0; k <concernedCase->visitorList.size(); k++){
					concernedCase->visitorList->moveGUI();
				}
			}
		}
	}*/
}
