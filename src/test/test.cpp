#include <iostream>
#include <string>
#include <map>

#include "../common/models/Field.hpp"


int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
    ClientField* field = new ClientField(Location(0,0));
    field->setShowOwnerColor(true);
    field->setOwnerID(5);
    std::cout<<field->getImageName()<<std::endl;
    return 0;

}
