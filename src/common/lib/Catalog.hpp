#ifndef CATALOG_HPP_
#define CATALOG_HPP_

#include <vector>
#include "Field.hpp"
#include "Player.hpp"

class Catalog{

	std::vector<Field*> fieldList;

public:
	Catalog();
	void putOnMarket(Field*);
	void getOffer(Player,Field*,int);
	void acceptOffer(Player,Field*,int);
	void give(Field*,Player);
	std::vector<Field*> getBuyable();
};

#endif // CATALOG_HPP_

