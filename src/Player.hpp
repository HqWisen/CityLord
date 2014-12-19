#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player{
	const int INITIALBUDGET;
	int money;
	std::list<Building*> buildingList;
	std::list<Field*> fieldList;
	City* city;
	public:
		Player() = default;
		void buildBuilding();
		void destroyBuilding();
		void makeOffer();
		void cancelOffer();
		void isBankrupt();
};

#endif // PLAYER_HPP_

