/*

Map.cpp

Matrice dans laquelle sera stockée la carte et les éléments de la ville (batiments, routes, ...)

*/
#include "Map.hpp"

using namespace std;

Map::Map(string nomDeLaCarte){ // metrre un fichier txt en paramètre
    string temp_string;
    ifstream file (nomDeLaCarte);
    getline(file, temp_string);
	dimensionX = atoi(temp_string.c_str());
    getline(file, temp_string);
    dimensionY = atoi(temp_string.c_str());
    //initialise la matrice
    mapMatrice = new Case**[dimensionX];
    for (int i=0; i<dimensionX; i++) { //creates matrix of nodes
        mapMatrice[i] = new Case*[dimensionY];
        for (int j=0; j<dimensionY; j++) {
            mapMatrice[i][j] = nullptr;
        }
    }
    //parseur
    for (int j=0; j<((dimensionY*2)+1); j++) { //par ligne
        getline(file, temp_string);
        char temp_char;
        if (j == 0) {
            for (int i=0; i<dimensionX; i++) { //par colonne
                temp_char = temp_string.at((i*4)+1);
                if (temp_char == ' ') {
                    mapMatrice[i][0] = new Road(i,0);
                    ((Road*) (mapMatrice[i][0]))->setPath(1, true);
                }
            }
        } else if (j == (dimensionY*2)) { 
            for (int i=0; i<dimensionX; i++) {
                temp_char = temp_string.at((i*4)+1);
                if (temp_char == ' ') {
                    ((Road*) (mapMatrice[i][dimensionY-1]))->setPath(3, true);
                }
            }
        }else if ((j % 2) == 0) {
            for (int i=0; i<dimensionX; i++) {
                temp_char = temp_string.at((i*4)+1);
                if (temp_char == ' ') {
                    if (mapMatrice[i][j/2] == nullptr) {
                        mapMatrice[i][j/2] = new Road(i,j/2);
                    }
                    ((Road*) (mapMatrice[i][j/2]))->setPath(1, true);
                    ((Road*) (mapMatrice[i][(j/2)-1]))->setPath(3, true);
                }
            }
        } else {
            temp_char = temp_string.at(0);
            if (temp_char == ' ') {
                if (mapMatrice[0][j/2] == nullptr) {
                    mapMatrice[0][j/2] = new Road(0,j/2);
                }
                ((Road*) (mapMatrice[0][j/2]))->setPath(0, true);
            } 
            for (int i=0; i<dimensionX; i++) {
                temp_char = temp_string.at((i*4));
                if (temp_char == ' ') {
                    if (mapMatrice[i-1][j/2] == nullptr) {
                        mapMatrice[i-1][j/2] = new Road(i-1,j/2);
                    }
                    if (mapMatrice[i][j/2] == nullptr) {
                        mapMatrice[i][j/2] = new Road(i,j/2);
                    }
                    ((Road*) (mapMatrice[i-1][j/2]))->setPath(2, true);
                    ((Road*) (mapMatrice[i][j/2]))->setPath(0, true);
                }
                temp_char = temp_string.at((i*4)+2);
                if (temp_char == 'B') {
                    mapMatrice[i][j/2] = new Obstacle(i,j/2);
                }else if (temp_char == 'X') {
                    mapMatrice[i][j/2] = new Obstacle(i,j/2);
                }else if (temp_char == 'P') {
                    mapMatrice[i][j/2] = new Obstacle(i,j/2);
                }else {
                    if (mapMatrice[i][j/2] == nullptr) {
                        mapMatrice[i][j/2] = new Road(i,j/2);
                    }
                }
            }
            temp_char = temp_string.at(dimensionX*4);
            if (temp_char == ' ') {
                ((Road*) (mapMatrice[dimensionX-1][j/2]))->setPath(2, true);
            } 
        }
    }
}

void Map::display(){
    for (int j=0; j<((dimensionY*2)+1); j++) { //prints labyrinth in output files
        if (j == (dimensionY*2)) {
            for (int i=0; i<dimensionX; i++) {
                if (((mapMatrice[i][dimensionY-1])->getType() == "Road") && \
                                            (((Road*) (mapMatrice[i][dimensionY-1]))->getPath(3) == true)) {
                    cout<<"+ ║ ";
                }else {
                    cout<<"+---";
                }
            }
            cout<<"+"<<endl;
        }else if ((j % 2) == 0) {
            for (int i=0; i<dimensionX; i++) {
                if (((mapMatrice[i][j/2])->getType() == "Road") && \
                                            ((Road*) (mapMatrice[i][j/2]))->getPath(1) == true) {
                    cout<<"+ ║ ";
                }else {
                    cout<<"+---";
                }
            }
            cout<<"+"<<endl;
        } else {
            for (int i=0; i<dimensionX; i++) {
                if (((mapMatrice[i][j/2])->getType() == "Road") && \
                                            ((Road*) (mapMatrice[i][j/2]))->getPath(0) == true) {
                    cout<<"═";
                    mapMatrice[i][j/2]->display();
                }else {
                    cout<<"|";
                    mapMatrice[i][j/2]->display();
                }
            }
            if (((mapMatrice[dimensionX-1][j/2])->getType() == "Road") && \
                                            ((Road*) (mapMatrice[dimensionX-1][j/2]))->getPath(2) == true) {
                cout<<"═"<<endl;
            }else {
                cout<<"|"<<endl;
            }
        }
    }
}

Map::~Map(){
    for (int i=0; i<dimensionX; i++) {
        for (int j=0; j<dimensionY; j++) {
            mapMatrice[i][j] = nullptr;
        }
    }
}

/*int main(int argc, const char* argv[]){
    Map map1 = Map("Map1.txt");
    map1.display();
	return 0;
}*/