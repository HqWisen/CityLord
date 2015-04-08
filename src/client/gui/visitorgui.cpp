#include "visitorgui.h"

const int VisitorGUI::MAXSTEP = 100;

VisitorGUI::VisitorGUI(ClientManagerGUI* cm, QGraphicsScene* sc) :
    QGraphicsPixmapItem(), movemutex(), inmutex(), NORTH(getImagePath("car_north")), SOUTH(getImagePath("car_south")), EAST(getImagePath("car_east")), WEST(getImagePath("car_west")), \
    moving(false), in(false), nextLocation(), currentLocation(), clientManager(cm), scene(sc){

}

VisitorGUI::~VisitorGUI(){
}


/*void VisitorGUI::run(){
    bool arrived;
    int counter;
    qreal stepx, stepy;
    QPointF pstart, pend, current;
    while(!aborting){
        movemutex.lock();
        if(moving){
            std::cout<<"gotoMOUVE"<<std::endl;
            pstart = carToIso(currentLocation, NORTH);
            pend = carToIso(nextLocation, NORTH);
            current = pstart;
            stepx = (pend.x() - pstart.x()) / (fluidity*10);
            stepy = (pend.y() - pstart.y()) / (fluidity*10);
            arrived = false;
            counter = 0;
        }
        while(moving && !arrived){
            current.setX(current.x() + stepx);
            current.setY(current.y() + stepy);
            std::cout<<"updating scene to "<<nextLocation.toString()<<".."<<std::endl;
            clientManager->updateScene(item, current);
            std::cout<<"advancing to "<<nextLocation.toString()<<".."<<std::endl;
            msleep(fluidity);
            counter++;
            arrived = counter == (fluidity*10);
        }
        if(moving){
            std::cout<<"OUTMOVING"<<std::endl;
            currentLocation = nextLocation;
            moving = false;
        }
        movemutex.unlock();
    }
}*/
void VisitorGUI::changeImage(Location current, Location next){
    int diffrow = current.getRow() - next.getRow();
    int diffcol = current.getCol() - next.getCol();
    if(diffrow == 0){
        setPixmap( diffcol > 0 ? WEST : EAST);
    }else if(diffcol == 0){
        setPixmap( diffrow > 0 ? NORTH : SOUTH);
   }else{
        int crow = current.getRow();
        int ccol = current.getCol();
        if(crow == 0 || ccol == 0){
            setPixmap( crow == 0 ? SOUTH : EAST);
        }else{
            setPixmap( crow == 19 ? NORTH : WEST);
        }
   }
}

void VisitorGUI::show(Location location){
    currentLocation = location;
    scene->addItem(this);
    changeImage(currentLocation, currentLocation);
    this->setOffset(carToIso(currentLocation, NORTH));
}

void VisitorGUI::advance(int phase){
    //std::cout<<"advance => ";
    if(!moving) return;
    //inmutex.lock();
    //std::cout<<"CAN ";
    currentLocation = nextLocation;

    if(!in){
       // movemutex.lock();
        in = true;
    }
    //std::cout<<"lock advance"<<std::endl;
    current.setX(current.x() + stepx);
    current.setY(current.y() + stepy);
    //setPos(mapToParent(current));
    setOffset(current);
    counter++;
    arrived = counter >= MAXSTEP;
    //std::cout<<"arrived = "<<arrived<<std::endl;
    if(arrived){
        //std::cout<<"REALEASE LOCK"<<std::endl;
        moving = false;
        //movemutex.unlock();
        in = false;
        //std::cout<<"unlock advance"<<std::endl;
    }
    //inmutex.unlock();
    //QPointF location = this->pos();
    //setPos(mapToParent(QPointF(0,-5)));
    //setPos(mapToParent(0,-(speed)));
}



void VisitorGUI::move(Location location){
    //std::cout<<"ASK TO MOVE TO "<<location.toString()<<std::endl;
    //movemutex.lock();
    //std::cout<<"lock move"<<std::endl;
    nextLocation = location;
    changeImage(currentLocation, nextLocation);
    pstart = carToIso(currentLocation, NORTH);
    pend = carToIso(nextLocation, NORTH);
    current = pstart;
    stepx = (pend.x() - pstart.x()) / (MAXSTEP);
    stepy = (pend.y() - pstart.y()) / (MAXSTEP);
    arrived = false;
    counter = 0;
    moving = true;
    //movemutex.unlock();
    //std::cout<<"unlock move"<<std::endl;
}

void VisitorGUI::remove(){
    scene->removeItem(this);
}
/*
void VisitorGUI::abort(){
    aborting = true;
    while(isRunning());
}*/

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
