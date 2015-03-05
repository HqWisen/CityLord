#ifndef SPAWN_HPP_
#define SPAWN_HPP_

#include "Road.hpp"

class Spawn{
	Road* spawnPoint;
	public:
		Road* getSpawnPoint(){return spawnPoint;};
        virtual ~Spawn() = default;
        virtual Visitor* spawn() = 0;
        virtual void despawn(Visitor*) = 0;
};

#endif // SPAWN_HPP_
