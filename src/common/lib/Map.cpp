#include "Map.hpp"

using namespace std;

/*
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

*/
