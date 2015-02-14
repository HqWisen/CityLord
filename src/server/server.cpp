#include "../common/socket/Socket.hpp"
#include "../common/socket/ServerSocket.hpp"
#include "../common/socket/ClientSocket.hpp"

#include <iostream>

#define PORT 5555

int main(){
	
	ServerSocket serverSocket(PORT);
  serverSocket.listen_clients();
  ClientSocket* clientSocket;
  std::cout<<"Beginning the server..."<<std::endl;
  std::string message;
  while(true){
  	clientSocket = serverSocket.accept_client();
  	std::cout<<clientSocket->getPeerInfos()<<std::endl;
  	message = clientSocket->read();
  	std::cout<<message<<std::endl;
  	
  }

	return 0;

}
