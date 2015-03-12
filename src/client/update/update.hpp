#ifndef UPDATE_HPP_
#define UPDATE_HPP_

#include "../CityLordClient.hpp"
#include "../../common/socket/SocketMessage.hpp"
#include <iostream>

class CityLordClient;

namespace update{
    void changeowner(CityLordClient*, SocketMessage);
    void changeownerwithbuilding(CityLordClient*, SocketMessage);
    void build(CityLordClient*, SocketMessage);
    void destroy(CityLordClient*, SocketMessage);
}

#endif // UPDATE_HPP_


