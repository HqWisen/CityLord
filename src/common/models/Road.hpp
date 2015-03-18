#ifndef ROAD_HPP_
#define ROAD_HPP_

#include <string>
#include "Case.hpp"

typedef const int direction_type;

class Road : public Case{
    protected:
        bool directions[4] = {false, false, false, false};
        std::string image;
        bool blocked = false;
    public:
        static direction_type NORTH, SOUTH, EAST, WEST;
	public:
		Road(Location);
		~Road() = default;
        std::string print() override;
        std::string getImageName() override;
        void open(direction_type);
        void generateImage();
        bool isOpen(direction_type);
        std::string toString();
        void setUpBarricade(bool);
        bool isBlocked();
};

#endif // ROAD_HPP_

