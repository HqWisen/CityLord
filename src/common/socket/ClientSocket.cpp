#include "ClientSocket.hpp"
ClientSocket::ClientSocket(int fd, struct sockaddr_in addr){
	sockfd = fd;
	client_addr = addr;
}

std::string ClientSocket::getClientIP(){
  std::string result = inet_ntoa(client_addr.sin_addr);
	return result;
}

