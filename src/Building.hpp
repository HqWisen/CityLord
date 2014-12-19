#ifndef BUILDING_HPP_
#define BUILDING_HPP_

class Building{
	const int MAXCAPACITY;
	int capacity;
	int price;
	//openTime
	//closeTime
	int income;
	int attractiveness;
	//dailyCost
	//visitors
	//level
	//constructionCost
	//destructionCost
	
	public:
		Building() = default;
		void deleteVisitor(Visitor);
		void receiveVisitor(Visitor);
		void upgrade();
};

#endif // BUILDING_HPP_

