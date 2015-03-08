#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <sstream>
#include "Case.hpp"
#include "BuildingType.hpp"
#include "Player.hpp"
#include "Building.hpp"
#include <string>

<<<<<<< HEAD
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
=======
class Field : public Case{			// public Case
    int price = 15000;
    Building* building = nullptr;
    Player* owner = nullptr;
    string color = "";
	public:
		Field(Location);
		Field(Location, Building*);
		Field(int, Location);
		Field(int, Location, Building*);
        std::string print() override;
        void buildBuilding(BuildingType);
		void destroyBuilding();
		int getPrice();
		void setPrice(int);
		Player* getOwner();
		string getColor();
>>>>>>> 67527cefd8236d939f70ac94f5dabb24fead0857
        string getOwnerColor();
};

class Field : public BasicField{
    Player* owner;
    public:
        Field(Location);
        Player* getOwner();
        void setOwner(Player*);
<<<<<<< HEAD
=======
		Building* getBuilding();
		bool hasOwner();
		bool hasColor();
		bool hasBuilding();
>>>>>>> 67527cefd8236d939f70ac94f5dabb24fead0857
        string toString();
        int getOwnerID() override;
        bool hasOwner() override;
};

class ClientField : public BasicField{
    int ownerid = -1;
    public:
        ClientField(Location);
        int getOwnerID() override;
        void setOwnerID(int);
        bool hasOwner() override;
};


#endif // FIELD_HPP_

