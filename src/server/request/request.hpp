#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include "../UserManager.hpp"
#include "../CityLordServer.hpp"
#include "../../common/socket/SocketMessage.hpp"
#include "../../common/models/BuildingType.hpp"
#include <pthread.h>
#include <iostream>

class UserManager;
class CityLordServer;

class RequestSystem{
static pthread_mutex_t requestmutex;
public:
	static SocketMessage login(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage createaccount(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage choicemap(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage createcity(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage cityinfo(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage numberofcity(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage joincity(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage selectfield(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage showinfo(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage showcatalog(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage buy(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage build(CityLordServer*, UserManager*, SocketMessage);
	static SocketMessage upgrade(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage destroy(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage mapfullupdate(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage leavecity(CityLordServer*, UserManager*, SocketMessage);
    static SocketMessage playerinfo(CityLordServer*, UserManager*, SocketMessage);
};

#endif // REQUEST_HPP_

