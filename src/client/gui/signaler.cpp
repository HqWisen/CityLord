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

void Signaler::signalActiving(std::string info, Location location){
    emit activeButton(info, location);
}
