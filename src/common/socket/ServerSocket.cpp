#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port) : Socket() {
	
	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);     // short, network byte order
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(server_addr.sin_zero), '\0', 8); // zero the rest of the struct
  
	if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
  }

}
void ServerSocket::listenClients(){
  if(listen(sockfd, BACKLOG) == -1){
    perror("listen");
  }
}

ClientSocket* ServerSocket::acceptClient(){

  unsigned int sin_size = sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr;
  int newfd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size);
  if(newfd == -1){
		perror("accept");
  }
  
  return new ClientSocket(newfd, client_addr);
}
