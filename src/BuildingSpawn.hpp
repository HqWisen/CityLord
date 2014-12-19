#ifndef BUILDINGSPAWN_HPP_
#define BUILDINGSPAWN_HPP_

class BuildingSpawn : public Spawnable, public Building{
	Road* spawnRoad;
	public:
		BuildingSpawn() = default;
};

#endif // BUILDINGSPAWN_HPP_

