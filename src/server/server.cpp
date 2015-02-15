#include <iostream>
#include "CityLordServer.hpp"

#define PORT 5555

int main(){
	CityLordServer server(PORT);
	server.run();
	return 0;
}
