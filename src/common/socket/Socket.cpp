#include "Socket.hpp"

const char* Socket::EOM = "\nEOM";

Socket::Socket(){
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
	}
	int yes = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
		perror("setsockopt");
	}
}

Socket::Socket(int fd){
	sockfd = fd;
}

void Socket::write(std::string message){
	message += EOM;
	const char* mess = message.c_str();
	int len = message.size();
	while(len > 0){
		if(send(sockfd, mess, strlen(mess) < MAXBUFSIZE-1 ? strlen(mess) : MAXBUFSIZE-1, 0) == -1){
			perror("send");
    }
    len -= MAXBUFSIZE-1;
    mess += MAXBUFSIZE-1;
  }
}

std::string Socket::read(){
	std::string message;
  int numbytes;
  // TODO  Probleme quand buffer plus de 1 carateres
  do{
   	numbytes = recv(sockfd, buffer, MAXBUFSIZE-1, 0);
    if(numbytes == -1){
    	message = "";
			perror("recv");
    }
    else if(numbytes == 0){
    	message = "";
			perror("recv connection");
			// FIXME handle disconnection
    }
    buffer[numbytes] = '\0';
		message += buffer;
	}while(message.find(EOM) == std::string::npos and numbytes > 0);
  if(message != ""){
  	message.erase(message.end() - strlen(EOM), message.end());
  }
	return message;
}

void Socket::writeInt(int number){
	std::string message(std::to_string(number));
	write(message);
}
int Socket::readInt(){
	std::string message = read();
	int number = std::stoi(message);
	return number;
}




