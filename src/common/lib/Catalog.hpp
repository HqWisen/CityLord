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
		void give(Field*, Player*);
        std::vector<Field*> getPurchasableFields();

};

#endif // CATALOG_HPP_

