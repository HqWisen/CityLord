#ifndef UPDATE_HPP_
#define UPDATE_HPP_

#include "../ClientManager.hpp"
#include "../../common/socket/SocketMessage.hpp"
#include <iostream>
#include <pthread.h>

class ClientManager;

class UpdateSystem{
static pthread_mutex_t updatemutex;
public:
    static void changeowner(ClientManager*, SocketMessage);
    static void build(ClientManager*, SocketMessage);
    static void destroy(ClientManager*, SocketMessage);
    static void updatemoney(ClientManager*, SocketMessage);
    static void updatetime(ClientManager*, SocketMessage);
    static void createvisitor(ClientManager*, SocketMessage);
    static void movevisitor(ClientManager*, SocketMessage);
    static void removevisitor(ClientManager*, SocketMessage);
    static void offer(ClientManager*, SocketMessage);
    static void offercancel(ClientManager*, SocketMessage);
};

#endif // UPDATE_HPP_


