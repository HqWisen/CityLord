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

/*
void Signaler::signalUpdatingTime(int newTime){
    emit updateTime(newTime);
}
*/
