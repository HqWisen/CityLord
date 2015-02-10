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

int Socket::write(std::string message){
  message += EOM;
  void sending(int* sock_pt, char* message, int length){
  if(send(*sock_pt, message, length, 0) == -1){
    exitbecause("chat", "sending");
  }
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



