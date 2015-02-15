#include <iostream>
#include "Road.hpp"

using namespace std;

Road::Road(int x, int y){
	path[4] = {false};
	coord=Location(x, y);
}

Road::~Road(){
	path[4] = {false};
	image="";
}

void Road::display(){
	cout<<image;
}

//getters & setters
bool Road::getPath(int i){
	return path[i];
}

void Road::setPath(int i, bool newRoad){ // ╬ ╝ ═ ║ ╚ ╠ ╣ ╔ ╗ ╦ ╩ □
	path[i]=newRoad;

	if (path[0] != false){
		if (path[1] != false){
			if (path[2] != false){
				if (path[3] != false){
					image="═╬═";
				}
				else {
					image="═╩═";
				}
			}else if (path[3] != false){
				image="═╣ ";
			}else {
				image="═╝ ";
			}
		}else if (path[2] != false){
			if (path[3] != false){
				image="═╦═";
			}else {
				image="═══"; 
			}
		}else if (path[3] != false){
			image="═╗ ";
		}else {
			image="═□ ";
		}
	}else if (path[1] != false){
		if (path[2] != false){
			if (path[3] != false){
				image=" ╠═";
			}else {
				image=" ╚═";
			}
		}else if (path[3] != false){
			image=" ║ ";
		}
	}else if (path[2] != false){
		if (path[3] != false){
			image=" ╔═";
		}else {
			image=" □═";
		}
	}else {
		image=" □ ";
	}
}