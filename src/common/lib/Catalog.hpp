#ifndef CATALOG_HPP_
#define CATALOG_HPP_

class Catalog{

	std::list<Building> buildingList;
	std::list<Field> fieldList;
	
	public:
		Catalog() = default;
		void putOnMaket();
		void makeOffer();
		void acceptOffer();
};

#endif // CATALOG_HPP_

