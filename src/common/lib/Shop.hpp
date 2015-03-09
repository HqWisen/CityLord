
#ifndef SHOP_HPP_
#define SHOP_HPP_

#include <sstream>
#include "Building.hpp"
#include <string>

class Shop : public Building{
    public:
        Shop(int level = 1);
        Shop();
        ~Shop() = default;
        //int getPrice(){return price;};
        //int getDestructionCost(){return destructionCost;};
        //void upgrade();
        //bool addVisitor();
        //void removeVisitor();
};

#endif // SHOP_HPP_

