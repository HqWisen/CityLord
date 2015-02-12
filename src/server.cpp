#include "Socket.hpp"
#include "ServerSocket.hpp"

#include <iostream>

#define PORT 5555

int main(){
  ServerSocket serverSocket(PORT);
  serverSocket.listen_clients();
  ClientSocket* clientSocket;
  while(true){
  	//clientSocket = serverSocket.accept_client();
  	//std::cout
  }
  
  
  
  
  /*std::string m = "Bonjour je m'apelle hakim et je suis la parce que toi aussi";
  const char* mc = m.c_str();
  std::cout<<mc<<std::endl;
  std::cout<<mc+2<<std::endl;

  std::cout<<m<<std::endl;
  std::cout<<m.at(2)<<std::endl;
  std::cout<<m.size()<<std::endl;*/

	return 0;

}
