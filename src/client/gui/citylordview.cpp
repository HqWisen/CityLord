#include "citylordview.h"
#include <iostream>

const int CityLordView::WIDTH = 1152;
const int CityLordView::HEIGHT = 804;

int px = 0, py = 0;
QPointF lastPos;
QPointF startMouse;
QGraphicsPixmapItem* itemtest;

CityLordView::CityLordView(QWidget* parent) :
    QGraphicsView(parent), scene(new QGraphicsScene(this)), BASE("src/resources/img/base.png"){
    resize(WIDTH, HEIGHT);
    setScene(scene);
    setSceneRect(-((WIDTH/2)-(BASE.width()/2)), 0, WIDTH-2, HEIGHT-2);
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

CityLordView::~CityLordView(){
    delete scene;
}

QPointF CityLordView::carToIso(int x, int y, int lagy = 0){
    return QPointF(x-y, ((x+y)/2) + lagy);
}


void CityLordView::isoToLoc(QPointF position){
    int posX=position.x();
    int posY=position.y();

    int cartX = ((2*(posY-37) + posX )/2)/75; // 152;
    int cartY = (((2*posY - posX )/2)+37)/75; // 75;

    std::cout<<" X = "<< cartX <<" Y = "<< cartY<<std::endl;

    //return Location(cartX,cartY);
}


void CityLordView::addBaseOn(int row, int col){
    int height = BASE.height();
    QGraphicsPixmapItem* item;
    item = scene->addPixmap(BASE);
    item->setOffset(carToIso(col*height, row*height));
}

void CityLordView::addBar(){

    QPixmap b("src/resources/img/grass75_darkBlue.png");
    QPixmap b1("src/resources/img/road.png");
    int height = BASE.height();
    int row, col;
    row = 8;
    col = 10;
    int isoX, isoY;
    int x, y;
    x = row*height;
    y = col*height;
    isoX = (x - y);
    isoY = ((x + y) / 2)-b.height() + height;
    QGraphicsPixmapItem* item;
    item = scene->addPixmap(b);
    itemtest = item;
    //item->setOffset(isoX, isoY);
    item->setOffset(carToIso((col+0)*height, (row+0)*height, -b.height()+BASE.height()));

    item = scene->addPixmap(b1);
    //item->setOffset(isoX, isoY);
    item->setOffset(carToIso((col+0)*height, (row+1)*height, -b1.height()+BASE.height()));
}

void CityLordView::mousePressEvent(QMouseEvent * e){

    /*QPointF pt = mapToScene(e->pos());
    scale(1.2, 1.2);*/
    startMouse = mapToScene(e->pos());
    std::cout<<"PRESSED"<<" X = "<< startMouse.x() <<" Y = "<< startMouse.y()<<std::endl;
    isoToLoc(startMouse);
    //rotate(-10);

}
void CityLordView::mouseReleaseEvent(QMouseEvent * e){
    QPixmap b("src/resources/img/museum_purple.png");
    itemtest->setPixmap(b);

    /*QPointF pt = mapToScene(e->pos());
    scale(1.2, 1.2);*/
    std::cout<<"RELEASE"<<std::endl;
    //rotate(-10);

}

void CityLordView::mouseMoveEvent(QMouseEvent * e){

    QPointF currentPos = mapToScene(e->pos());
    if(startMouse.x() < currentPos.x()){
        int move = currentPos.x()-startMouse.x();
        px-= move;
        lastPos.setX(lastPos.x()-move);
    }else{
        int move = startMouse.x()-currentPos.x();
        px+= move;
        lastPos.setX(lastPos.x()+move);
    }
    if(startMouse.y() < currentPos.y()){
        int move = currentPos.y()-startMouse.y();
        py-=move;
        lastPos.setY(lastPos.y()-move);
    }else{
        int move = startMouse.y()-currentPos.y();
        py+=move;
        lastPos.setY(lastPos.y()+move);
    }
    lastPos = currentPos;
    setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);

    //scale(1.2, 1.2);
    std::cout<<"MOVED X = "<<px<<std::endl;
    std::cout<<"MOVED Y = "<<py<<std::endl;
    //std::cout<<rect().x()<<std::endl;
    //rect().;
    //rotate(-10);

}

void CityLordView::wheelEvent(QWheelEvent* e){
    QPointF currentPos = mapToScene(e->pos());

    if(e->delta() > 0){
        scale(1.1, 1.1);
    }
    else if(e->delta() < 0){
        scale(0.9, 0.9);
    }


}

/*
void CityLordView::contextMenuEvent(QContextMenuEvent* e){
    std::cout<<"SOUFIANE"<<std::endl;
}*/

void CityLordView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:
            py-=30;
            lastPos.setY(lastPos.y() - 30);
            break;
        case Qt::Key_Left:
            px-=30;
            lastPos.setX(lastPos.x() - 30);
            break;
        case Qt::Key_Right:
            px+=30;
            lastPos.setX(lastPos.x() +30);
            break;
        case Qt::Key_Down:
            py+=30;
           lastPos.setY(lastPos.y() + 30);
            break;
    }
    setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);
}
