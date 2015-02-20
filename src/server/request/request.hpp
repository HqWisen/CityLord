#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include "../UserManager.hpp"
#include "../CityLordServer.hpp"
#include "../../common/socket/SocketMessage.hpp"
#include "../../common/lib/BuildingType.hpp"

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
	SocketMessage showmap(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage mapsize(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage selectfield(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage showinfo(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage showcatalog(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage buy(CityLordServer*, UserManager*, SocketMessage);
	SocketMessage build(CityLordServer*, UserManager*, SocketMessage);

}

#endif // REQUEST_HPP_

