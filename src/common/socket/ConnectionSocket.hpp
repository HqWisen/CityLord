#ifndef CONNECTION_SOCKET_HPP_
#define CONNECTION_SOCKET_HPP_

#include <string>
#include "Socket.hpp"

class ConnectionSocket : public Socket{
	struct sockaddr_in server_addr;
	public:
		ConnectionSocket(char* hostname, int port);
		std::string getServerInfos();		
};

#endif // CONNECTION_SOCKET_HPP_

