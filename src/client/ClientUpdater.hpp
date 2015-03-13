#ifndef UPDATER_HPP_
#define UPDATER_HPP_

#include "../common/socket/Socket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/thread/Thread.hpp"
#include "update/update.hpp"
#include "ClientManager.hpp"

class ClientManager;

typedef void (* update_ptr)(ClientManager*, SocketMessage);

class ClientUpdater : public Thread{

    static const std::map<std::string, update_ptr> updatemap;


    ClientManager* clientManager;
    Socket updateSocket;
    public:
        ClientUpdater(ClientManager*, Socket);
        void run() override;
        void recvUpdate(SocketMessage&);
        void sendAnswer(SocketMessage);

};

#endif // UPDATER_HPP_

