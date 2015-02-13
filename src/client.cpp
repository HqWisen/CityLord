#include "Socket.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"

#include <iostream>

#define PORT 5555

int main(int argc, char** argv){
  if(argc != 2){
    printf("Hostname not given !");
    return 1;
  }
  char* hostname = argv[1];
	ClientSocket clientSocket(hostname, PORT);
  clientSocket.write("Hakim boulahya|");
	std::cout<<clientSocket.getPeerInfos()<<std::endl;
	return 0;

}
