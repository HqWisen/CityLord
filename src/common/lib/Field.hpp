#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <sstream>
#include "Case.hpp"
#include "BuildingType.hpp"
#include "Player.hpp"
#include "Building.hpp"
#include <string>

class BasicField : public Case{
    protected:
        int price = 15000;
        Building* building = nullptr;
    public:
        BasicField(Location);
        virtual ~BasicField() = default;
        string print() override;
        void buildBuilding(BuildingType);
        void destroyBuilding();
        int getPrice();
        void setPrice(int);
        Building* getBuilding();
        bool hasBuilding();
        virtual int getOwnerID() = 0;
        virtual bool hasOwner() = 0;
        string getOwnerColor();
};

class Field : public BasicField{
    Player* owner;
    public:
        Field(Location);
        Player* getOwner();
        void setOwner(Player*);
        string toString();
        int getOwnerID() override;
        bool hasOwner() override;
};

class ClientField : public BasicField{
    int ownerid = -1;
    public:
        ClientField(Location);
        void setOwnerID(int);
        int getOwnerID() override;
        bool hasOwner() override;
};


#endif // FIELD_HPP_

