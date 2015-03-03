#include "defaultwidget.h"

DefaultWidget::DefaultWidget(QWidget *parent, ClientManager* cm) :
    QWidget(parent), clientManager(cm), backgroundFrame(this){
}

DefaultWidget::~DefaultWidget(){

}

void DefaultWidget::displayDefaultBackground(){
    backgroundFrame.setGeometry(0, 0, 1152, 864);
    backgroundFrame.setStyleSheet("background-image: url(src/resources/img/BgCityBig.jpg)");
}

