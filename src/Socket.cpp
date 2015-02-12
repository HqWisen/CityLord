#include "Socket.hpp"

Socket::Socket(){
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket :");
	}
	int yes = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
		perror("setsockopt :");
	}
}

Socket::Socket(int fd){
	sockfd = fd;
}

int Socket::write(std::string message){
	const char* mess = message.c_str();
	unsigned int len = message.size();
	while(len > 0){
		if(send(sockfd, mess, MAXBUFSIZE-1, 0) == -1){
			perror("send :");
    }
    len -= MAXBUFSIZE-1;
    mess += MAXBUFSIZE-1;
  }
  if(send(sockfd, EOM, strlen(EOM), 0) == -1){
			perror("send :");
  }
	return 0;
}

int Socket::read(std::string& message){
  
  int numbytes;
  do{
    numbytes = recv(sockfd, buffer, MAXBUFSIZE-1, 0);
    if(numbytes == -1){
      return -1; // Error
    }
    else if(numbytes == 0){
      return 0; // FIXME Connection problem
    }
    buffer[numbytes] = '\0';
    message += buffer;
  }while(message.find(EOM) == std::string::npos);
  
  
  return 0;
}



