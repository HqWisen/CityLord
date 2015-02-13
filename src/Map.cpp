/*

Map.cpp

Matrice dans laquelle sera stockée la carte et les éléments de la ville (batiments, routes, ...)

*/

#include <iostream>
#include <fstream>
#include "Map.hpp"

 
using namespace std;

Map::Map(char* nomDeLaMap){ // metrre un fichier txt en paramètre
	dimensionX = tailleMaxLong;
	dimensionY = tailleMaxLarg;
}

//Map::~Map(){}

//Map::Map(const Map &s);

void Map::display(){
	for(int j=0;j<tailleMaxLarg;j++) {
    	cout<<"-----";
    }  
	for(int i=0;i<tailleMaxLong;i++) {
		cout<<"| ";
    	for(int j=0;j<tailleMaxLarg;j++) {
        	Case *caseCourante = matrice[i][j];
        	caseCourante->display();
        	cout<<" | ";
        }    
		cout<<endl;
    	for(int j=0;j<tailleMaxLarg;j++) {
        	cout<<"-----";
        }    
		cout<<endl;
	}
}

int main( int argc, const char* argv[] )
{
	return 0;
}
