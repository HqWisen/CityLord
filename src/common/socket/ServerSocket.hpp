#ifndef SERVER_SOCKET_HPP_
#define SERVER_SOCKET_HPP_

#include <string>
#include "Socket.hpp"
#include "ClientSocket.hpp"

#define BACKLOG 10

class ServerSocket : public Socket{
	public:
		ServerSocket(int port);
		void listenClients();
		ClientSocket* acceptClient();
		
};


#endif // SERVER_SOCKET_HPP_

