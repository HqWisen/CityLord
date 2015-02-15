#include <iostream>
#include "Road.hpp"

using namespace std;

Road::Road(int x, int y){
	coord=Location(x, y);
}

Road::~Road(){
	path[4] = {nullptr};
	image="";
}

void Road::display(){
	cout<<image;
}

//getters & setters
Road* Road::getPath(int i){
	return path[i];
}

void Road::setPath(int i, Road* newRoad){ // ╬ ╝ ═ ║ ╚ ╠ ╣ ╔ ╗ ╦ ╩ □
	path[i]=newRoad;

	if (path[0] != NULL){
		if (path[1] != NULL){
			if (path[2] != NULL){
				if (path[3] != NULL){
					image="═╬═";
				}
				else {
					image="═╩═";
				}
			}else if (path[3] != NULL){
				image="═╣ ";
			}else {
				image="═╝ ";
			}
		}else if (path[2] != NULL){
			if (path[3] != NULL){
				image="═╦═";
			}else {
				image="═══"; 
			}
		}else if (path[3] != NULL){
			image="═╗ ";
		}else {
			image="═□ ";
		}
	}else if (path[1] != NULL){
		if (path[2] != NULL){
			if (path[3] != NULL){
				image=" ╠═";
			}else {
				image=" ╚═";
			}
		}else if (path[3] != NULL){
			image=" ║ ";
		}
	}else if (path[2] != NULL){
		if (path[3] != NULL){
			image=" ╔═";
		}else {
			image=" □═";
		}
	}else {
		image=" □ ";
	}
}