#ifndef UPDATE_HPP_
#define UPDATE_HPP_

#include "../ClientManager.hpp"
#include "../../common/socket/SocketMessage.hpp"
#include <iostream>

class ClientManager;

class UpdateMethods{
public:
    static void changeowner(ClientManager*, SocketMessage);
    static void changeownerwithbuilding(ClientManager*, SocketMessage);
    static void build(ClientManager*, SocketMessage);
    static void destroy(ClientManager*, SocketMessage);
    static void visitormove(ClientManager*, SocketMessage);
};

#endif // UPDATE_HPP_


