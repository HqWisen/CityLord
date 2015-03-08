#ifndef ROAD_HPP_
#define ROAD_HPP_

#include <string>
#include "Case.hpp"

typedef const int direction_type;

class Road : public Case{
    bool directions[4] = {false, false, false, false};
    std::string image;
    public:
        static direction_type NORTH, SOUTH, EAST, WEST;
	public:
		Road(Location);
		~Road() = default;
        std::string print(); // override
        void open(direction_type);
        bool isOpen(direction_type);
        std::string toString();

};

#endif // ROAD_HPP_

