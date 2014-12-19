#ifndef MAP_HPP_
#define MAP_HPP_

class Map{
	int dimension;
	Neighborhood neighborhoods[];
	public:
		Map() = default;
		void display();
};

#endif // MAP_HPP_

