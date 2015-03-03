#include "widgetmanager.h"
#include "defaultwidget.h"

const key_type WidgetManager::LOGIN = 0;
const key_type WidgetManager::CREATEACCOUNT = 1;
const key_type WidgetManager::MAINMENU = 2;
const key_type WidgetManager::INPLAY = 3;
const key_type WidgetManager::CREATEGAME = 4;
const key_type WidgetManager::JOINGAME = 5;


WidgetManager::WidgetManager() : stackedWidget(new QStackedWidget), layout(new QVBoxLayout), pages(){
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stackedWidget);
}

WidgetManager::~WidgetManager(){
    // FIXME SEGMENTION FAULT
    //delete layout;
    //delete stackedWidget;
    /*for(std::map<int, QWidget*>::iterator iterator = pages.begin(); iterator != pages.end(); iterator++) {
        std::cout<<"first = "<<iterator->first<<std::endl;
        std::cout<<"second = "<<iterator->second<<std::endl;
        //delete iterator->second;
    }*/
}


void WidgetManager::set(key_type key, DefaultWidget* widget){
    if(!alreadySet(key)){
        pages[key] = widget;
        stackedWidget->addWidget(widget);
    }else{
        throw std::invalid_argument("This key is already set.");
    }
}

DefaultWidget* WidgetManager::get(key_type key){
    if(alreadySet(key)){
        return pages[key];
    }else{
        return nullptr;
    }
}

bool WidgetManager::alreadySet(key_type key){
    auto search = pages.find(key);
    return search != pages.end();
}

void WidgetManager::setCurrentWidget(key_type key){
    get(key)->refresh();
    stackedWidget->setCurrentWidget(get(key));
}

QVBoxLayout* WidgetManager::getLayout(){
    return layout;
}
