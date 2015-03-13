#include "defaultwidget.h"

DefaultWidget::DefaultWidget(QWidget *parent, ClientManagerGUI* cm) :
    QWidget(parent), clientManager(cm), backgroundFrame(this){
}

DefaultWidget::~DefaultWidget(){

}

void DefaultWidget::displayDefaultBackground(){
    backgroundFrame.setGeometry(0, 0, 1152, 864);
    backgroundFrame.setStyleSheet("background-image: url(src/resources/img/BgCityBig.jpg)");
}

void DefaultWidget::displayLogo(QWidget *parent,int x, int y){
    QWidget *frame = new QWidget(parent);
    frame->setGeometry(x, y, 400, 150);
    frame->setStyleSheet("background-image: url(src/resources/img/CityLordLogo.png)");
}
