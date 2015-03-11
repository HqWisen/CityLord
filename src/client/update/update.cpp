#include "update.hpp"

namespace update{
    void changeowner(CityLordClient* client, SocketMessage update){
        Location location = Location::parse(update.get("location"));
        int ownerid = std::stoi(update.get("ownerid"));
        ClientField* field = dynamic_cast<ClientField*>(client->getMap()->getCase(location));
        field->setOwnerID(ownerid);
    }
}


