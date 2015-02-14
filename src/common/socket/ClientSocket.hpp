#ifndef CLIENT_SOCKET_HPP_
#define CLIENT_SOCKET_HPP_

#include <string>
#include "Socket.hpp"

class ClientSocket : public Socket{
	struct sockaddr_in client_addr;
	public:
		ClientSocket(int fd, struct sockaddr_in addr);
		//ClientSocket(char* hostname, int port);
		std::string getClientInfos();		
};

#endif // CLIENT_SOCKET_HPP_

