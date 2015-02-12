#ifndef SOCKET_HPP_
#define SOCKET_HPP_

// FIXME nettoyer les includes

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>



#define MAXBUFSIZE 100
#define EOM "#EOM#" // End of message

class Socket{
  public:
		Socket();
		Socket(int fd);
		int write(std::string);
		int read(std::string&);
  protected:
    int sockfd;
    char buffer[MAXBUFSIZE];
	
};

#endif // SOCKET_HPP_

