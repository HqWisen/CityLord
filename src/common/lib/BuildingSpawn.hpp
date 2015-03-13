#ifndef BUILDINGSPAWN_HPP_
#define BUILDINGSPAWN_HPP_

#include "Case.hpp"
#include "Spawn.hpp"

class BuildingSpawn : public Case, public Spawn{
	public:
		BuildingSpawn(Location);
        std::string print() override;
        std::string getImageName() override;
        ~BuildingSpawn() = default;
		//Location spawn() override;
		//void despawn(Visitor*) override;
};

#endif // BUILDINGSPAWN_HPP_

