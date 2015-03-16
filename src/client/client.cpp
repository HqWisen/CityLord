#include <iostream>
#include "CityLordClient.hpp"
#define PORT 27000

int main(int argc, char** argv){
  char* hostname;
  if(argc != 2){
    printf("Hostname not given !\n");
  	hostname = "localhost";
  }
	else{
		hostname = argv[1];
	}
    CityLordClient client(hostname, PORT);
    client.runClient();
	return 0;
}
