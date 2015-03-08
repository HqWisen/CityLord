/*

Map.cpp

Matrice dans laquelle sera stockée la carte et les éléments de la ville (batiments, routes, ...)

*/
#include "Map.hpp"

using namespace std;

Map::Map(string fileName){
    string tmpString;
    ifstream file(fileName);
    getline(file, tmpString);
    numberOfCols = atoi(tmpString.c_str());
    getline(file, tmpString);
    numberOfRows = atoi(tmpString.c_str());
    //----------------------------------------------- Matrice  --------------------------------
    caseMatrix = new Case**[numberOfRows];
    for (int i=0; i<numberOfRows; i++) {
        caseMatrix[i] = new Case*[numberOfCols];
        for (int j=0; j<numberOfCols; j++) {
            caseMatrix[i][j] = nullptr;
        }
    }
    //----------------------------------------------- Parseur  --------------------------------
    Road* road;
    for (int row=0; row<((numberOfRows*2)+1); row++) { //par ligne
        getline(file, tmpString);
        char tmpChar;
        // ---------------------------------------- Premiere Ligne ----------------------------
        if (row == 0) {
            for (int col=0; col<numberOfCols; col++) { //par colonne
                tmpChar = tmpString.at((col*4)+1);
                if (tmpChar == ' ') {
                    road = new Road(Location(row, col));
                    caseMatrix[0][col] = road;
                    road->open(Road::NORTH);
                }
            }
        // ---------------------------------------- Derniere Ligne ----------------------------
        } else if (row == (numberOfRows*2)) {
            for (int col=0; col<numberOfCols; col++){
                tmpChar = tmpString.at((col*4)+1);
                if (tmpChar == ' ') {
                    road = dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col]);
                    road->open(Road::SOUTH);
                }
            }
        // ------------------- Lignes Intermediaires (partie au-dessus des cases) -------------
        }else if ((row % 2) == 0) {
            for (int col=0; col<numberOfCols; col++) {
                tmpChar = tmpString.at((col*4)+1);
                if (tmpChar == ' ') {
                    if (caseMatrix[row/2][col] == nullptr) {
                        caseMatrix[row/2][col] = new Road(Location(row/2, col));
                    }
                    dynamic_cast<Road*>(caseMatrix[row/2][col])->open(Road::NORTH);
                    dynamic_cast<Road*>(caseMatrix[(row/2)-1][col])->open(Road::SOUTH);
                }
            }
        // ------------------------ Lignes Intermediaires (milieu des cases) -------------------
        } else {
            // ---------------------------- Premiere case --------------------------------------
            tmpChar = tmpString.at(0);
            if (tmpChar == ' ') {

                if (caseMatrix[row/2][0] == nullptr) {
                    caseMatrix[row/2][0] = new Road(Location(row/2, 0));
                }
                dynamic_cast<Road*>(caseMatrix[row/2][0])->open(Road::WEST);
            }
            tmpChar = tmpString.at(2);
            if (tmpChar == 'B') {
                tmpChar = tmpString.at(1);
                int player = tmpChar;
                tmpChar = tmpString.at(3);
                int building = (int) tmpChar;
                BuildingType type = BuildingType::getTypeByIndex((building/10)-2);
                int level = (building%10);
                if (level == 0){
                    level = 10;
                }
                if (player > 47){
                    caseMatrix[row/2][0] = new Field(player-8, Location(row/2,0), new Building(type, level));
                }else {
                    caseMatrix[row/2][0] = new Field(Location(row/2,0), new Building(type, level));
                }
            }else if (tmpChar == 'O') {
                caseMatrix[row/2][0] = new Obstacle(Location(row/2, 0));
            }else if (tmpChar == 'F'){
                tmpChar = tmpString.at(1);
                int player = tmpChar;
                if (player > 47){
                    caseMatrix[row/2][0] = new Field(player-8, Location(row/2,0));
                }else {
                    caseMatrix[row/2][0] = new Field(Location(row/2,0));
                }
            }else if(tmpChar == 'R'){
                if (caseMatrix[row/2][0] == nullptr) {
                    caseMatrix[row/2][0] = new Road(Location(row/2, 0));
                }
            }
            // -------------------------- Cases suivantes --------------------------------------
            for (int col=1; col<numberOfCols; col++) {
                tmpChar = tmpString.at((col*4));
                if (tmpChar == ' ') {

                    if (caseMatrix[row/2][col-1] == nullptr) {
                        caseMatrix[row/2][col-1] = new Road(Location(row/2, col-1));
                    }
                    dynamic_cast<Road*>(caseMatrix[row/2][col-1])->open(Road::EAST);

                    if (caseMatrix[row/2][col] == nullptr) {
                        caseMatrix[row/2][col] = new Road(Location(row/2, col));
                    }
                    dynamic_cast<Road*>(caseMatrix[row/2][col])->open(Road::WEST);

                }
                tmpChar = tmpString.at((col*4)+2);
                if (tmpChar == 'B') {
                    tmpChar = tmpString.at((col*4)+1);
                    int player = tmpChar;
                    tmpChar = tmpString.at((col*4)+3);
                    int building = (int) tmpChar;
                    BuildingType type = BuildingType::getTypeByIndex((building/10)-2);
                    int level = (building%10);
                    if (level == 0){
                        level = 10;
                    }
                    if (player > 47){
                        caseMatrix[row/2][col] = new Field(player-8, Location(row/2,col), new Building(type, level));
                    }else {
                        caseMatrix[row/2][col] = new Field(Location(row/2,col), new Building(type, level));
                    }
                }if (tmpChar == 'O') {
                    caseMatrix[row/2][col] = new Obstacle(Location(row/2, col));
                }else if (tmpChar == 'F'){
                    tmpChar = tmpString.at(1);
                    int player = tmpChar;
                    if (player > 47){
                        caseMatrix[row/2][col] = new Field(player-8, Location(row/2,col));
                    }else {
                        caseMatrix[row/2][col] = new Field(Location(row/2,col));
                    }
                }else if(tmpChar == 'R') {
                    if (caseMatrix[row/2][col] == nullptr){
                        caseMatrix[row/2][col] = new Road(Location(row/2, col));
                    }
                }
            }
            // ---------------------------- Dernier 'mur' --------------------------------------
            tmpChar = tmpString.at(numberOfCols*4);
            if (tmpChar == ' ') {
                dynamic_cast<Road*>(caseMatrix[row/2][numberOfCols-1])->open(Road::EAST);
            }
        }
    }
    file.close();
}

void Map::display(){
    string color;
    Road* road;
    Field* field;

    for (int row=0; row<((numberOfRows*2)+1); row++) {
        if (row == (numberOfRows*2)) {
            for (int col=0; col<numberOfCols; col++) {
                if((road = dynamic_cast<Road*>(caseMatrix[numberOfRows-1][col])) && road->isOpen(Road::SOUTH)){
                    cout<<"+ ║ ";
                }else{
                    cout<<"+---";
                }
            }
            cout<<"+"<<endl;
        }else if ((row % 2) == 0) {
            for (int col=0; col<numberOfCols; col++) {
                if((road = dynamic_cast<Road*>(caseMatrix[row/2][col])) && road->isOpen(Road::NORTH)){
                    cout<<"+ ║ ";
                }else {
                    cout<<"+---";
                }
            }
            cout<<"+"<<endl;
        }else{
            for (int col=0; col<numberOfCols; col++) {
                if(((road = dynamic_cast<Road*>(caseMatrix[row/2][col]))) && road->isOpen(Road::WEST)){
                    cout<<"═";
                    cout<<(caseMatrix[row/2][col]->print());
                }else {
                    cout<<"|";
                    if((field = dynamic_cast<Field*>(caseMatrix[row/2][col]))){
                        if(field->hasOwner()){
                            color = field->getOwnerColor();
                        }else{
                            color="\033[0m";
                        }
                        string item = caseMatrix[row/2][col]->print();
                        cout<<color<<(((item.replace(0,1," ")).replace(2,1," ")) + "\033[0m");
                    }else {
                        cout<<(caseMatrix[row/2][col]->print());
                    }
                }
            }
            if((road = dynamic_cast<Road*>(caseMatrix[row/2][numberOfCols-1])) && road->isOpen(Road::EAST)){
                cout<<" "<<endl;
            }else{
                cout<<"|"<<endl;
            }
        }
    }
}

Map::~Map(){
    delete[] caseMatrix;
    //delete[] visitorList;
}

Case* Map::getCase(Location coord){
    return caseMatrix[coord.getRow()][coord.getCol()];
}

int Map::getNumberOfCols(){
    return numberOfCols;
}

int Map::getNumberOfRows(){
    return numberOfRows;
}

/*string Map::getMapString(){
    string output = "";
    Road* road;
    Field* field;
    output += (to_string(numberOfCols)) + "\n";
    output += (to_string(numberOfRows)) + "\n";
    for (int row=0; row<((numberOfRows*2)+1); row++) {
        if (row == (numberOfRows*2)) {
            for (int col=0; col<numberOfCols; col++) {

                if ((road = dynamic_cast<Road*>(caseMatrix[col][numberOfRows-1])) && \
                                            (((Road*) (caseMatrix[col][numberOfRows-1]))->getPath(3) == true)) {
                    output += "+   ";
                }else {
                    output += "+---";
                }
            }
            output += "+\n";
        }else if ((row % 2) == 0) {
            for (int col=0; col<numberOfCols; col++) {
                if ((road = dynamic_cast<Road*>(caseMatrix[col][row/2])) && \
                                            ((Road*) (caseMatrix[col][row/2]))->getPath(1) == true) {
                    output += "+   ";
                }else {
                    output += "+---";
                }
            }
            output += "+\n";
        } else {
            for (int col=0; col<numberOfCols; col++) {
                if ((road = dynamic_cast<Road*>(caseMatrix[col][row/2])) && \
                                            ((Road*) (caseMatrix[col][row/2]))->getPath(0) == true) {
                    output += "  R ";
                }else {
                    output += "|";
                    if ((field = dynamic_cast<Field*>(caseMatrix[col][row/2]))) {
                        output += (caseMatrix[col][row/2])->print();
                    }else {
                        output += " O ";
                    }

                }
            }
            if ((road = dynamic_cast<Road*>(caseMatrix[numberOfCols-1][row/2])) && \
                                            ((Road*) (caseMatrix[numberOfCols-1][row/2]))->getPath(2) == true) {
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
}*/


/*int main(int argc, const char* argv[]){
    //int col = '0';
    //cout<<col<<endl;
    Map map1 = Map("Map1.txt");
    map1.display();
    //string lel = map1.getMapString();
    //Map::parseMap("out.txt", lel);
    return 0;
}*/
