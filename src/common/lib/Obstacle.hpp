#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include "Case.hpp"

class Obstacle: public Case{
	public:
		Obstacle(Location);
		~Obstacle() = default;
        std::string print() override;
};

#endif // OBSTACLE_HPP_
