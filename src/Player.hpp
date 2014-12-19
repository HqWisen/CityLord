#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player{
	const int INITIALBUDGET;
	int money;
	public:
		Player() = default;
		void buildBuilding();
		void destroyBuilding();
		void makeOffer();
		void cancelOffer();
		void isBankrupt();
};

#endif // PLAYER_HPP_

