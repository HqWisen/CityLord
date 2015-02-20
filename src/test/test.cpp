#include <iostream>
#include <string>
#include <map>

#include "../common/lib/Map.hpp"
#include "../server/CityManager.hpp"
int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
	CityManager cm("resources/maps/Map1.txt", 0);
	//Map* map = cm.getMap();
  cm.test();
	return 0;

}
