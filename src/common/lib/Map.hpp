/*

Map.hpp

Matrice dans laquelle sera stockée la carte et les éléments de la ville (batiments, routes, ...)

*/
#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include "Case.hpp"
//#include "Neighborhood.hpp"
//#include "Field.hpp"
#include "Road.hpp"
#include "Obstacle.hpp"
#include "Building.hpp"

using namespace std;

const int tailleMaxLong=6; // Longueur maximale de la carte
const int tailleMaxLarg=10; // Largueur maximale de la carte
const int nombreDeCases = tailleMaxLarg*tailleMaxLong;

class Map{
	int dimensionX;
	int dimensionY;
	//Neighborhood neighborhoods[];
	Case*** mapMatrice;
public:
	Map(string nomDeLaCarte); // metrre un fichier txt en paramètre
	~Map();
	void display();
	Case* getCase(int,int);
};

#endif // MAP_HPP_

