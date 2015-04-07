#include "visitorgui.h"


VisitorGUI::VisitorGUI(QObject *parent, QGraphicsScene* sc) :
    QThread(parent), movemutex(), NORTH(getImagePath("car_north")), SOUTH(getImagePath("car_south")), EAST(getImagePath("car_east")), WEST(getImagePath("car_west")), \
    moving(false), nextLocation(), currentLocation(), scene(sc), item(new QGraphicsPixmapItem){

}

VisitorGUI::~VisitorGUI(){
    delete item;
}


void VisitorGUI::run(){
    std::cout<<"RUNNING VISITOR"<<std::endl;
    bool arrived;
    int counter;
    while(true){
        movemutex.lock();
        /*QPointF pstart(carToIso(currentLocation, NORTH)), pend(carToIso(nextLocation, NORTH));
        QPointF current(pstart);
        arrived = false;
        counter = 0;*/
        while(moving/* && !arrived*/){
            /*std::cout<<"start "<<pstart.x()<<", "<<pstart.y()<<"; end "<<pend.x()<<", "<<pend.y()<<std::endl;
            std::cout<<"current = "<<current.x()<<", "<<current.y()<<std::endl;
            if(currentLocation.getRow() == nextLocation.getRow()){
                int step = (pstart.x() - pend.x()) / 100;
                std::cout<<"stepX "<<step<<std::endl;
                current.setX(current.x() + step);
            }
            else{
                int step = (pstart.y() - pend.y()) / 100;
                std::cout<<"stepY "<<step<<std::endl;
                current.setY(current.y() + step);
            }
            item->setOffset(current);
            msleep(10);
            counter++;
            arrived = counter == 100;*/
            item->setOffset(carToIso(nextLocation, NORTH));
            moving = false;
        }
        /*if(moving){
            currentLocation = nextLocation;
        }*/
        moving = false;
        movemutex.unlock();
    }
}

void VisitorGUI::show(Location location){
    currentLocation = location;
    scene->addItem(item);
    item->setPixmap(NORTH);
    item->setOffset(carToIso(currentLocation, NORTH));
    //start();
}

void VisitorGUI::move(Location location){
    nextLocation = location;
    /*movemutex.lock();
    moving = true;
    movemutex.unlock();*/
    item->setOffset(carToIso(nextLocation, NORTH));

}

void VisitorGUI::remove(){

    //exit();
    scene->removeItem(item);
}

QPointF VisitorGUI::carToIso(Location location, const QPixmap& pixmap){
    int x, y, lag, isoX, isoY;
    x = location.getCol()*NORTH.height();
    y = location.getRow()*NORTH.height();
    lag = NORTH.height() - pixmap.height();
    isoX = x-y;
    isoY = ((x+y)/2) + lag;
    return QPointF(isoX, isoY);
}

const char* VisitorGUI::getImagePath(std::string imagename){
    std::string path = QCoreApplication::applicationDirPath().toStdString()+"/src/resources/img/"+imagename+".png";
    return path.c_str();
}
