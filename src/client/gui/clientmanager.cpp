#include "clientmanager.h"
#include "defaultwidget.h"

<<<<<<< HEAD:src/client/gui/clientmanager.cpp
const key_type ClientManager::LOGIN = 0;
const key_type ClientManager::CREATEACCOUNT = 1;
const key_type ClientManager::MAINMENU = 2;
const key_type ClientManager::INPLAY = 3;
const key_type ClientManager::CREATEGAME = 4;
=======
const key_type WidgetManager::LOGIN = 0;
const key_type WidgetManager::CREATEACCOUNT = 1;
const key_type WidgetManager::MAINMENU = 2;
const key_type WidgetManager::INPLAY = 3;
const key_type WidgetManager::CREATEGAME = 4;
const key_type WidgetManager::JOINGAME = 5;

>>>>>>> 8947808f1fbea653d2706b8cb98785f6eaf305c8:src/client/gui/widgetmanager.cpp

ClientManager::ClientManager() : stackedWidget(new QStackedWidget), layout(new QVBoxLayout), pages(){
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stackedWidget);
}

ClientManager::~ClientManager(){
    // FIXME SEGMENTION FAULT
    //delete layout;
    //delete stackedWidget;
    /*for(std::map<int, QWidget*>::iterator iterator = pages.begin(); iterator != pages.end(); iterator++) {
        std::cout<<"first = "<<iterator->first<<std::endl;
        std::cout<<"second = "<<iterator->second<<std::endl;
        //delete iterator->second;
    }*/
}


void ClientManager::set(key_type key, DefaultWidget* widget){
    if(!alreadySet(key)){
        pages[key] = widget;
        stackedWidget->addWidget(widget);
    }else{
        throw std::invalid_argument("This key is already set.");
    }
}

DefaultWidget* ClientManager::get(key_type key){
    if(alreadySet(key)){
        return pages[key];
    }else{
        return nullptr;
    }
}

bool ClientManager::alreadySet(key_type key){
    auto search = pages.find(key);
    return search != pages.end();
}

void ClientManager::setCurrentWidget(key_type key){
    get(key)->refresh();
    stackedWidget->setCurrentWidget(get(key));
}

QVBoxLayout* ClientManager::getLayout(){
    return layout;
}
