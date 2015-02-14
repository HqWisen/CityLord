#ifndef CLIENT_SOCKET_HPP_
#define CLIENT_SOCKET_HPP_

#include <string>
#include "Socket.hpp"

class ClientSocket : public Socket{
	struct sockaddr_in peer_addr;
	public:
		ClientSocket(int fd, struct sockaddr_in addr);
		ClientSocket(char* hostname, int port);
		std::string getPeerInfos();		
};

#endif // CLIENT_SOCKET_HPP_

