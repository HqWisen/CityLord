#ifndef SERVER_SOCKET_HPP_
#define SERVER_SOCKET_HPP_

#include <string>
#include "Socket.hpp"
#include "ClientSocket.hpp"

#define BACKLOG 10

class ServerSocket : public Socket{
	public:
		ServerSocket(int port);
		void listen_clients();
		ClientSocket* accept_client();
		
};


#endif // SERVER_SOCKET_HPP_

