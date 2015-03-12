#include <iostream>
#include <string>
#include <map>

#include "../common/lib/Map.hpp"

int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
    Map<Field> map("src/resources/maps/CITYBAY.txt");
    map.display();
    return 0;

}
