#ifndef CATALOG_HPP_
#define CATALOG_HPP_

#include <vector>
#include "Offer.hpp"
#include "../socket/SocketMessage.hpp"


class Catalog{

	std::vector<Field*> fieldVector;
	std::vector<Offer*> offerVector;

	public:
		Catalog() = default;
		void putOnMarket(Field*);
		void putOfferOnMarket(Offer*);
		bool isOnMarket(Field*);
		int isOfferOnMarket(Field*);
		void give(Field*, Player*);
		void removeOffer(int);
        std::vector<Field*> getPurchasableFields();
        std::vector<Offer*> getOffers();

};

#endif // CATALOG_HPP_

