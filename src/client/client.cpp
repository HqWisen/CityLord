#include <iostream>
#include "CityLordClient.hpp"
#define PORT 5555

int main(int argc, char** argv){
  if(argc != 2){
    printf("Hostname not given !\n");
    return 1;
  }
  char* hostname = argv[1];
  CityLordClient client(hostname, PORT);
  client.run();
	return 0;
}
