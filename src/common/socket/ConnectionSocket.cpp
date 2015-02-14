#include "ConnectionSocket.hpp"

ConnectionSocket::ConnectionSocket(char* hostname, int port) : Socket(){
	struct hostent* he;
	he = gethostbyname(hostname);
	if(he == NULL){
		perror("gethostbyname :");
	}
	server_addr.sin_family = AF_INET;         // host byte order
	server_addr.sin_port = htons(port);     // short, network byte order
	memset(&(server_addr.sin_zero), '\0', 8); // zero the rest of the struct
	server_addr.sin_addr = *((struct in_addr*)he->h_addr);
	
	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1){
    printf("Connection to the server is impossible\n");
    perror("connect");
  }
}

std::string ConnectionSocket::getServerInfos(){
  std::string result = inet_ntoa(server_addr.sin_addr);
	return result;
}

