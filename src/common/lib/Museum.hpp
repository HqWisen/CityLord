
#ifndef MUSEUM_HPP_
#define MUSEUM_HPP_

#include <sstream>
#include "Building.hpp"
#include <string>

class Museum : public Building{
    public:
        Museum(int level = 1);
        Museum();
        ~Museum() = default;
        //int getPrice(){return price;};
        //int getDestructionCost(){return destructionCost;};
        //void upgrade();
        //bool addVisitor();
        //void removeVisitor();
};

#endif // MUSEUM_HPP_

