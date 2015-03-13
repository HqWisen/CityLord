#include "BorderSpawn.hpp"

BorderSpawn::BorderSpawn(Location location) : Road(location) {
	spawnPoint = this->getLocation();
}

BorderSpawn::BorderSpawn(Location location, Road* oldRoad) : Road(location){
	if (oldRoad->isOpen(Road::NORTH)){
		this->open(Road::NORTH);
	}
	if (oldRoad->isOpen(Road::SOUTH)){
		this->open(Road::SOUTH);
	}
	if (oldRoad->isOpen(Road::WEST)){
		this->open(Road::WEST);
	}
	if (oldRoad->isOpen(Road::EAST)){
		this->open(Road::EAST);
	}
	spawnPoint = this->getLocation();
	delete oldRoad;
}

std::string BorderSpawn::getImageName(){
    return toString();
}

//Visitor* BorderSpawn::spawn() {return nullptr;}

//void BorderSpawn::despawn(Visitor*) {}

