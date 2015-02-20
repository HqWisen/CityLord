#ifndef CATALOG_HPP_
#define CATALOG_HPP_

#include <vector>
#include "Field.hpp"
#include "Player.hpp"
#include "../socket/SocketMessage.hpp"


class Catalog{

	std::vector<Field*> fieldVector;

	public:
		Catalog() = default;
		void putOnMarket(Field*);
		bool isOnMarket(Field*);
		std::vector<Field*> getPurchasableFields();
		void give(Field*, Player*);
};
	/*void getOffer(Player,Field*,int);
	void acceptOffer(Player,Field*,int);
	
};
*/
#endif // CATALOG_HPP_

