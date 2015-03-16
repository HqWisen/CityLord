#include <iostream>
#include "CityLordServer.hpp"

#define PORT 27000

int main(){
	CityLordServer server(PORT);
	server.runServer();
	return 0;
}
