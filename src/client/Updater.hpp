#ifndef UPDATER_HPP_
#define UPDATER_HPP_

#include "../common/socket/Socket.hpp"
#include "../common/socket/SocketMessage.hpp"
#include "../common/thread/Thread.hpp"
#include "update/update.hpp"
#include "CityLordClient.hpp"

class CityLordClient;

typedef void (* update_ptr)(CityLordClient*, SocketMessage);

class Updater : public Thread{

    static const std::map<std::string, update_ptr> updatemap;

    CityLordClient* client = nullptr;
    Socket updateSocket;
    public:
        Updater(CityLordClient*, Socket);
		void run() override;
        void recvUpdate(SocketMessage&);
};

#endif // UPDATER_HPP_

