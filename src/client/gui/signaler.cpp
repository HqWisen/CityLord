#include "signaler.h"

Signaler::Signaler()
{
}
void Signaler::signalRepainting(){
    emit repaintView();
}

void Signaler::signalBuildViewMap(){
    emit buildViewMap();
}

void Signaler::signalActiving(SocketMessage message, Location location){
    emit selectField(message, location);
}

void Signaler::signalUpdatingMoney(int newMoney){
    emit updateMoney(newMoney);
}

void Signaler::signalUpdatingTime(std::string time){
    emit updateTime(time.c_str());
}

void Signaler::signalCreatingVisitor(int id, Location location){
    emit createVisitor(id, location.toString().c_str());
}

void Signaler::signalMovingVisitor(int id, Location location){
    emit moveVisitor(id, location.toString().c_str());
}

void Signaler::signalRemovingVisitor(int id){
    emit removeVisitor(id);
}

void Signaler::signalUpdatingScene(QGraphicsPixmapItem* item, QPointF point){
    emit updateScene(item, point);
}
