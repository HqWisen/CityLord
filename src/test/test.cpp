#include <iostream>
#include <string>
#include <map>

#include "../common/lib/Map.hpp"

int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
    Map map("src/resources/maps/Citytown.txt");
    std::cout<<map.getNumberOfRows()<<std::endl;
    std::cout<<map.getNumberOfCols()<<std::endl;
    map.display();
    return 0;

}
