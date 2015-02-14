#include "CityLordServer.hpp"

#include <iostream>

#define PORT 5555

int main(){
	CityLordServer server(PORT);
	server.run();
	
	/*ServerSocket serverSocket(PORT);
  serverSocket.listen_clients();
  ClientSocket* clientSocket;
  std::string message;
  std::cout<<"Beginning the server..."<<std::endl;
  while(true){
  	clientSocket = serverSocket.accept_client();
  	std::cout<<clientSocket->getClientInfos()<<std::endl;
  	message = clientSocket->read();
  	std::cout<<message<<std::endl;
  	
  }*/

	return 0;

}
