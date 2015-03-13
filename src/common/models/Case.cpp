#include "Case.hpp"

Case::Case(int row, int col) : location(row, col){
}

Case::Case(Location loc) : location(loc){
}

Location Case::getLocation(){
    return location;
}

void Case::setLocation(Location loc){
    location = loc;
}

bool Case::isField(){
    return false;
}
