#ifndef BORDERSPAWN_HPP_
#define BORDERSPAWN_HPP_

#include "Road.hpp"
#include "Spawn.hpp"

class BorderSpawn : public Road, public Spawn{
	public:
		BorderSpawn(Location);
        BorderSpawn(Location, Road*);
        ~BorderSpawn() = default;
        std::string getImageName() override;
        //Visitor* spawn() override;
        //void despawn(Visitor*) override;
};

#endif // BORDERSPAWN_HPP_
