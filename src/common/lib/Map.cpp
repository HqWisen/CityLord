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
                    mapMatrice[i][0] = new Road(Location(i,0));
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
                        mapMatrice[i][j/2] = new Road(Location(i,j/2));
                    }
                    ((Road*) (mapMatrice[i][j/2]))->setPath(1, true);
                    ((Road*) (mapMatrice[i][(j/2)-1]))->setPath(3, true);
                }
            }
        } else {
            temp_char = temp_string.at(0);
            if (temp_char == ' ') {
                if (mapMatrice[0][j/2] == nullptr) {
                    mapMatrice[0][j/2] = new Road(Location(0,j/2));
                }
                ((Road*) (mapMatrice[0][j/2]))->setPath(0, true);

            } 
            temp_char = temp_string.at(2);
            if (temp_char == 'B') {
                //temp_char = temp_string.at(1);
                //int player = temp_char;
                temp_char = temp_string.at(3);
                int building = (int) temp_char;
                BuildingType type = BuildingType::getTypeByIndex((building/10)-2);
                int level = (building%10);
                if (level == 0){
                    level = 10;
                }
                mapMatrice[0][j/2] = new Field(Location(0,j/2), new Building(type, level));
            }else if (temp_char == 'X') {
                mapMatrice[0][j/2] = new Obstacle(Location(0,j/2));
            }else if (temp_char == 'F') {
                mapMatrice[0][j/2] = new Field(Location(0,j/2));
            }else {
                if (mapMatrice[0][j/2] == nullptr) {
                    mapMatrice[0][j/2] = new Road(Location(Location(0,j/2)));
                }
            }
            for (int i=1; i<dimensionX; i++) {
                temp_char = temp_string.at((i*4));
                if (temp_char == ' ') {
                    if (mapMatrice[i-1][j/2] == nullptr) {
                        mapMatrice[i-1][j/2] = new Road(Location(i-1,j/2));
                    }
                    if (mapMatrice[i][j/2] == nullptr) {
                        mapMatrice[i][j/2] = new Road(Location(i,j/2));
                    }
                    ((Road*) (mapMatrice[i-1][j/2]))->setPath(2, true);
                    ((Road*) (mapMatrice[i][j/2]))->setPath(0, true);
                }
                temp_char = temp_string.at((i*4)+2);
                if (temp_char == 'B') {
                    //temp_char = temp_string.at(1);
                    //int player = temp_char;
                    temp_char = temp_string.at((i*4)+3);
                    int building = (int) temp_char;
                    BuildingType type = BuildingType::getTypeByIndex((building/10)-2);
                    int level = (building%10);
                    if (level == 0){
                        level = 10;
                    }
                    mapMatrice[i][j/2] = new Field(Location(i,j/2), new Building(type, level));
                }else if (temp_char == 'X') {
                    mapMatrice[i][j/2] = new Obstacle(Location(i,j/2));
                }else if (temp_char == 'F') {
                    mapMatrice[i][j/2] = new Field(Location(i,j/2));
                }else {
                    if (mapMatrice[i][j/2] == nullptr) {
                        mapMatrice[i][j/2] = new Road(Location(i,j/2));
                    }
                }
            }
            temp_char = temp_string.at(dimensionX*4);
            if (temp_char == ' ') {
                ((Road*) (mapMatrice[dimensionX-1][j/2]))->setPath(2, true);
            } 
        }
    }
    file.close();
}

void Map::display(){
    string color;
    for (int j=0; j<((dimensionY*2)+1); j++) {
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
                    cout<<(mapMatrice[i][j/2]->display());
                }else {
                    cout<<"|";
                    if (((mapMatrice[i][j/2])->getType() == "Field")) {
                        if(((Field*) (mapMatrice[i][j/2]))->hasOwner()){
                            color = ((Field*) (mapMatrice[i][j/2]))->getOwner()->getColor();
                        }else {
                            color="\033[0m";
                        }
                        string item = mapMatrice[i][j/2]->display();
                        cout<<color<<(((item.replace(0,1," ")).replace(2,1," ")) + "\033[0m");
                    }else {
                        cout<<(mapMatrice[i][j/2]->display());
                    }
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
            delete mapMatrice[i][j];
        }
    }
}

Case* Map::getCase(Location coord){
    return mapMatrice[coord.getX()][coord.getY()];
}

string Map::getMapString(){
    string output = "";
    output += (to_string(dimensionX)) + "\n";
    output += (to_string(dimensionY)) + "\n";
    for (int j=0; j<((dimensionY*2)+1); j++) {
        if (j == (dimensionY*2)) {
            for (int i=0; i<dimensionX; i++) {
                if (((mapMatrice[i][dimensionY-1])->getType() == "Road") && \
                                            (((Road*) (mapMatrice[i][dimensionY-1]))->getPath(3) == true)) {
                    output += "+   ";
                }else {
                    output += "+---";
                }
            }
            output += "+\n";
        }else if ((j % 2) == 0) {
            for (int i=0; i<dimensionX; i++) {
                if (((mapMatrice[i][j/2])->getType() == "Road") && \
                                            ((Road*) (mapMatrice[i][j/2]))->getPath(1) == true) {
                    output += "+   ";
                }else {
                    output += "+---";
                }
            }
            output += "+\n";
        } else {
            for (int i=0; i<dimensionX; i++) {
                if (((mapMatrice[i][j/2])->getType() == "Road") && \
                                            ((Road*) (mapMatrice[i][j/2]))->getPath(0) == true) {
                    output += "  ";
                    output += (mapMatrice[i][j/2]->getType())[0];
                    output += " ";
                }else {
                    output += "|";
                    if ((mapMatrice[i][j/2])->getType() != "Field"){
                        output += " ";
                        output += (mapMatrice[i][j/2]->getType())[0];
                        output += " ";
                    }else {
                        output += (mapMatrice[i][j/2])->display();
                    }

                }
            }
            if (((mapMatrice[dimensionX-1][j/2])->getType() == "Road") && \
                                            ((Road*) (mapMatrice[dimensionX-1][j/2]))->getPath(2) == true) {
                output += " \n";
            }else {
                output += "|\n";
            }
        }
    }
    return output;
}

void Map::parseMap(string filePath, string map){
    ofstream file (filePath);
    file << map;
    file.close();
}


int main(int argc, const char* argv[]){
    char i = 20;
    cout<<i<<endl;
    Map map1 = Map("Map1.txt");
    map1.display();
    string lel = map1.getMapString();
    Map::parseMap("out.txt", lel);
	return 0;
}
