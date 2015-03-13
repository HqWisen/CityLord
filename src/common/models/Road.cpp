#include "Road.hpp"

#include <iostream>

const int Road::WEST = 0;
const int Road::NORTH = 1;
const int Road::EAST = 2;
const int Road::SOUTH = 3;

Road::Road(Location location) : Case(location){
}

std::string Road::print(){
    return image;
    //return toString();
}

std::string Road::getImageName(){
    return toString();
}

// ╬ ╝ ═ ║ ╚ ╠ ╣ ╔ ╗ ╦ ╩ □

void Road::open(direction_type dir){
    directions[dir]=true;
    if (directions[WEST]){
        if (directions[NORTH]){
            if (directions[EAST]){
                if (directions[SOUTH]){
					image="═╬═";
				}
				else {
					image="═╩═";
				}
            }else if (directions[SOUTH]){
				image="═╣ ";
			}else {
				image="═╝ ";
			}
        }else if (directions[EAST]){
            if (directions[SOUTH]){
				image="═╦═";
			}else {
				image="═══"; 
			}
        }else if (directions[SOUTH]){
			image="═╗ ";
		}else {
			image="═□ ";
		}
    }else if (directions[NORTH]){
        if (directions[EAST]){
            if (directions[SOUTH]){
				image=" ╠═";
			}else {
				image=" ╚═";
			}
        }else if (directions[SOUTH]){
			image=" ║ ";
		}else {
			image=" □ ";
		}
    }else if (directions[EAST]){
        if (directions[SOUTH]){
			image=" ╔═";
		}else {
			image=" □═";
		}
	}else {
		image=" □ ";
    }
}

bool Road::isOpen(direction_type dir){
    return directions[dir];
}

std::string Road::toString(){
    std::string result = "";
    result +=  directions[NORTH] ? "N" :"" ;
    result +=  directions[SOUTH] ? "S" :"" ;
    result +=  directions[EAST] ? "E" :"" ;
    result +=  directions[WEST] ? "W" :"" ;
    return result;
}
