#ifndef SOCKET_HPP_
#define SOCKET_HPP_

// FIXME nettoyer les includes

#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXBUFSIZE 4

class Socket{
	static const char* EOM; // End of message
  public:
		Socket();
		Socket(int fd);
		int write(std::string);
		std::string read();
  protected:
    int sockfd;
    char buffer[MAXBUFSIZE];
	
};

#endif // SOCKET_HPP_

