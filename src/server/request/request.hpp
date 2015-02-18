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
	SocketMessage createaccount(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage choicemap(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage createcity(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage choicecity(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage joincity(CityLordServer*, UserManager*, SocketMessage);
}

#endif // REQUEST_HPP_

