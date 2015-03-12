#ifndef OFFER_HPP_
#define OFFER_HPP_

#include "Field.hpp"
#include "Player.hpp"

class Offer{
	Player* owner;
	Field* ownedField;
	int offeredPrice;
	public:
		Offer() = default;
		Offer(Player*, Field*, int);
		Player* getOwner();
		Field* getField();
		int getPrice();
		~Offer();
};

#endif //OFFER_HPP_

