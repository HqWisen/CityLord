#ifndef SPAWN_HPP_
#define SPAWN_HPP_

#include "Road.hpp"
#include "../../server/Visitor.hpp"

class Spawn{
	protected:
		Location spawnPoint;
	public:
		Location getSpawnPoint(){return spawnPoint;};
		void setSpawnPoint(Location newSpawnPoint){spawnPoint = newSpawnPoint;};
        virtual ~Spawn() = default;
        //virtual Visitor* spawn() = 0;
        //virtual void despawn(Visitor*) = 0;
};

#endif // SPAWN_HPP_
