#ifndef OFFER_HPP_
#define OFFER_HPP_


#include "Player.hpp"
#include "../common/models/Field.hpp"

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

