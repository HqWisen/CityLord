#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include "../UserManager.hpp"
#include "../CityLordServer.hpp"
#include "../../common/socket/SocketMessage.hpp"

#include <iostream>

class UserManager;
class CityLordServer;

namespace request{
	SocketMessage login(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage createAccount(CityLordServer*, UserManager*, SocketMessage);
}

#endif // REQUEST_HPP_

