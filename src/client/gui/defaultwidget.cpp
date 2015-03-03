#include "defaultwidget.h"

DefaultWidget::DefaultWidget(QWidget *parent, WidgetManager* wm) :
    QWidget(parent), widgetManager(wm), backgroundFrame(this){
}

DefaultWidget::~DefaultWidget(){

}

void DefaultWidget::displayDefaultBackground(){
    backgroundFrame.setGeometry(0, 0, 1152, 864);
    backgroundFrame.setStyleSheet("background-image: url(src/resources/img/BgCityBig.jpg)");
}

void DefaultWidget::displayLogo(QWidget *parent,int x, int y){
    QWidget *frame = new QWidget(parent);
    frame->setGeometry(100, 100, 400, 150);
    frame->setStyleSheet("background-image: url(src/resources/img/CityLordLogo.png)");
}
