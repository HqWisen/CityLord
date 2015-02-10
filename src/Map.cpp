/*

Map.cpp

Matrice dans laquelle sera stockée la carte et les éléments de la ville (batiments, routes, ...)

*/

#include<iostream>
#include "Map.hpp"

using namespace std;


Map::Map(): dimensionX(tailleMaxLong), dimensionY(tailleMaxLarg){}

//Map::~Map(){}

//Map::Map(const Map &s);

void Map::display(){
	for(int i=0;i<tailleMaxLong;i++) {
    	for(int j=0;j<tailleMaxLarg;j++) {
        	//Case caseCourante = matrice[i][j];
        	//caseCourante.display();
        }    
		cout<<endl;
	}
}
