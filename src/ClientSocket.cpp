#include "ClientSocket.hpp"
ClientSocket::ClientSocket(int fd, struct sockaddr_in addr){
	sockfd = fd;
	peer_addr = addr;
}

ClientSocket::ClientSocket(char* hostname, int port) : Socket(){
	struct hostent* he;
	he = gethostbyname(hostname);
	if(he == NULL){
		perror("gethostbyname :");
	}
	peer_addr.sin_family = AF_INET;         // host byte order
	peer_addr.sin_port = htons(port);     // short, network byte order
	memset(&(peer_addr.sin_zero), '\0', 8); // zero the rest of the struct
	peer_addr.sin_addr = *((struct in_addr*)he->h_addr);
	
	if(connect(sockfd, (struct sockaddr *)&peer_addr, sizeof(struct sockaddr)) == -1){
    printf("Connection to the server is impossible\n");
    perror("connect :");
  }
}

std::string ClientSocket::getPeerInfos(){
  std::string result = inet_ntoa(peer_addr.sin_addr);
	return result;
}

