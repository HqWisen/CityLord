#ifndef CATALOG_HPP_
#define CATALOG_HPP_

#include <vector>

class Catalog{

	std::vector<Field*> fieldList;
	
	public:
		Catalog() = default;
		void putOnMarket(Field);
		void getOffer(Player,Field*,int);
		void acceptOffer(Player,Field*,int);
		void give(Player player,Field* field);
		std::vector<Field*> getBuyable();
};

#endif // CATALOG_HPP_

