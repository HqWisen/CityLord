#include "BuildingSpawn.hpp"

BuildingSpawn::BuildingSpawn(Location location, Location spawnRoad) : Case(location) {
	spawnPoint = spawnRoad;
}

std::string BuildingSpawn::print(){
	return " S ";
}

//Visitor* BuildingSpawn::spawn() {return nullptr;}

//void BuildingSpawn::despawn(Visitor*) {}


