#include "clientmanagerGUI.h"
#include "defaultwidget.h"

const key_type ClientManagerGUI::LOGIN = 0;
const key_type ClientManagerGUI::CREATEACCOUNT = 1;
const key_type ClientManagerGUI::MAINMENU = 2;
const key_type ClientManagerGUI::INGAME = 3;
const key_type ClientManagerGUI::CREATEGAME = 4;
const key_type ClientManagerGUI::JOINGAME = 5;

const int ClientManagerGUI::SQUAREMAPSIZE = 20;

ClientManagerGUI::ClientManagerGUI(char* hostname, int port) :
    ClientManager(hostname, port),
    stackedWidget(new QStackedWidget), layout(new QVBoxLayout), pages(), signaler(new Signaler), currentPlayerID(-1){

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stackedWidget);
}

ClientManagerGUI::~ClientManagerGUI(){
    delete signaler;
    // FIXME SEGMENTION FAULT
    //delete layout;
    //delete stackedWidget;
    /*for(std::map<int, QWidget*>::iterator iterator = pages.begin(); iterator != pages.end(); iterator++) {
        std::cout<<"first = "<<iterator->first<<std::endl;
        std::cout<<"second = "<<iterator->second<<std::endl;
        //delete iterator->second;
    }*/
}


void ClientManagerGUI::set(key_type key, DefaultWidget* widget){
    if(!alreadySet(key)){
        pages[key] = widget;
        stackedWidget->addWidget(widget);
    }else{
        throw std::invalid_argument("This key is already set.");
    }
}

DefaultWidget* ClientManagerGUI::get(key_type key){
    if(alreadySet(key)){
        return pages[key];
    }else{
        return nullptr;
    }
}

bool ClientManagerGUI::alreadySet(key_type key){
    auto search = pages.find(key);
    return search != pages.end();
}

void ClientManagerGUI::setCurrentWidget(key_type key){
    get(key)->refresh();
    stackedWidget->setCurrentWidget(get(key));
}


QVBoxLayout* ClientManagerGUI::getLayout(){
    return layout;
}

void ClientManagerGUI::buildMap(std::string filename){
    ClientManager::buildMap(filename);
    signaler->signalBuildViewMap();
}

void ClientManagerGUI::repaint(){
   signaler->signalRepainting();
}

void ClientManagerGUI::updateMoney(int newMoney){
   signaler->signalUpdatingMoney(newMoney);
}


void ClientManagerGUI::updateTime(std::string time){
   signaler->signalUpdatingTime(time);
}

Signaler* ClientManagerGUI::getSignaler(){
    return signaler;
}

int ClientManagerGUI::getCurrentPlayerID(){
    return currentPlayerID;
}

void ClientManagerGUI::setCurrentPlayerID(int newID){
    currentPlayerID = newID;
}

