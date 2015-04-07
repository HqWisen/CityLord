#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <sstream>
#include <algorithm>
#include "Case.hpp"
#include "BuildingType.hpp"
#include "Building.hpp"
#include <string>

#include "../socket/SocketMessage.hpp"
#include "../../server/Player.hpp"

class BasicField : public Case{
    protected:
        int price = 15000;
        Building* building = nullptr;
        bool showOwnerColor;
        int offeredPrice = 0;
    public:
        BasicField(Location);
        virtual ~BasicField() = default;
        string print() override;

        //void buildBuilding(string);
        void buildBuilding(BuildingType, int level = 1);
        void destroyBuilding();
        int getPrice();
        void setPrice(int);
        int getOfferedPrice();
        void setOfferedPrice(int);
        Building* getBuilding();
        bool hasBuilding();
        virtual int getOwnerID() = 0;
        virtual bool hasOwner() = 0;
        string getOwnerColor();
        int getTotalPurchasePrice();
        bool isField() override;
        void setShowOwnerColor(bool);
        std::string getImageName() override;

};

class Field : public BasicField{
    Player* owner;
    public:
        Field(Location);
        ~Field(){destroyBuilding();};
        Player* getOwner();
        void setOwner(Player*);
        string toString();
        int getOwnerID() override;
        bool hasOwner() override;
        SocketMessage infoHasSocketMessage();
};

class ClientField : public BasicField{
    int ownerid = -1;
    public:
        ClientField(Location);
        ~ClientField(){destroyBuilding();};
        void setOwnerID(int);
        int getOwnerID() override;
        bool hasOwner() override;
};


#endif // FIELD_HPP_

