#ifndef BORDERSPAWN_HPP_
#define BORDERSPAWN_HPP_

#include "Road.hpp"
#include "Spawn.hpp"

class BorderSpawn : public Road, public Spawn{
	public:
        BorderSpawn(Road*);
        ~BorderSpawn() = default;
        Visitor* spawn() override;
        void despawn(Visitor*) override;
};

#endif // BORDERSPAWN_HPP_
