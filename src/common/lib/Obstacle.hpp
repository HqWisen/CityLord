#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include "Case.hpp"

class Obstacle: public Case{  // : public Case
	public:
		Obstacle() = default;
		void display();
};

#endif // OBSTACLE_HPP_

