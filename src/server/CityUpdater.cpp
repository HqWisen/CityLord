#include "CityUpdater.hpp"

CityUpdater::CityUpdater(){
    this->start();
}

void CityUpdater::generateVisitors(){
	std::cout<<"Visitor"<<std::endl;
}

void CityUpdater::updateBuildings(){
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

void CityUpdater::makeVisitorsAdvance(){
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

void CityUpdater::updateCity(){
	generateVisitors();
	updateBuildings();
	makeVisitorsAdvance();
}

void CityUpdater::run(){
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


