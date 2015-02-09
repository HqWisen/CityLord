/*

Map.hpp

Matrice dans laquelle sera stockée la carte et les éléments de la ville (batiments, routes, ...)

*/


#ifndef MAP_HPP_
#define MAP_HPP_

#include "Case.hpp"
#include "Neighborhood.hpp"

const int tailleMaxLong=5; // Longueur maximale de la carte
const int tailleMaxLarg=8; // Largueur maximale de la carte
const int nombreDeCases = tailleMaxLarg*tailleMaxLong;

class Map{
	int dimensionX;
	int dimensionY;
	Neighborhood neighborhoods[];
	Case matrice[tailleMaxLong][tailleMaxLarg];
	public:
		Map();		
		void display();
};

#endif // MAP_HPP_

