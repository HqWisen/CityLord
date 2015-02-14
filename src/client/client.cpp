#include "../common/socket/ConnectionSocket.hpp"

#include <iostream>

#define PORT 5555

int main(int argc, char** argv){
  if(argc != 2){
    printf("Hostname not given !\n");
    return 1;
  }
  char* hostname = argv[1];
	ConnectionSocket connectionSocket(hostname, PORT);
  std::cout<<"Server infos = "<<connectionSocket.getServerInfos()<<std::endl;
  connectionSocket.write("Hakim boulahya|");
	return 0;
}
