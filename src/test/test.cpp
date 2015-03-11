#include <iostream>
#include <string>
#include <map>

#include "../common/lib/Location.hpp"

int main(){
	/* main de test */
	std::cout<<">>> Beginning test <<<"<<std::endl;
    Location location(267,852);
    std::string source = location.toString();
    Location parsed = Location::parse(source);
    std::cout<<parsed.getRow()<<std::endl;
    std::cout<<parsed.getCol()<<std::endl;

    return 0;

}
