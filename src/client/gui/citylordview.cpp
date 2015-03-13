#include "citylordview.h"
#include <iostream>

const int CityLordView::WIDTH = 1152;
const int CityLordView::HEIGHT = 804;



CityLordView::CityLordView(QWidget* parent):
    QGraphicsView(parent), scene(new QGraphicsScene(this)), BASE(getImagePath("base")), map(nullptr), previousSelectedLocation(-1, -1){
    resize(WIDTH, HEIGHT);
    setScene(scene);
    setSceneRect(-((WIDTH/2)-(BASE.width()/2)), 0, WIDTH-2, HEIGHT-2);
    this->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    itemArray = new QGraphicsPixmapItem**[20];
    for(int i=0;i<20;i++){
        itemArray[i] = new QGraphicsPixmapItem*[20];
        for(int j=0;j<20;j++){
            itemArray[i][j] = new QGraphicsPixmapItem;
            scene->addItem(itemArray[i][j]);
        }
    }
}

CityLordView::~CityLordView(){
    delete scene;
    delete[] itemArray;
}

/*QPointF CityLordView::carToIso(int x, int y, int lagy = 0){
    return QPointF(x-y, ((x+y)/2) + lagy);
}*/

const char* CityLordView::getImagePath(std::string imagename){
    std::string path = QCoreApplication::applicationDirPath().toStdString()+"/src/resources/img/"+imagename+".png";
    return path.c_str();
}


QPointF CityLordView::carToIso(Location location, const QPixmap& pixmap){
    int x, y, lag, isoX, isoY;
    x = location.getCol()*BASE.height();
    y = location.getRow()*BASE.height();
    lag = BASE.height() - pixmap.height();
    isoX = x-y;
    isoY = ((x+y)/2) + lag;
    return QPointF(isoX, isoY);
}

Location CityLordView::isoToLoc(QPointF position){
    int posX=position.x();
    int posY=position.y();

    int cartX = ((2*(posY-37) + posX )/2)/75; // 152;
    int cartY = (((2*posY - posX )/2)+37)/75; // 75;
    return Location(cartY, cartX);
}

void CityLordView::setPlayedMap(Map<ClientField>* mapPlayed){
    map = mapPlayed;
}

void CityLordView::setRepaintSignaler(RepaintSignaler* s){
    signaler = s;
}


void CityLordView::mousePressEvent(QMouseEvent * e){

    startMouse = mapToScene(e->pos());
    Location location = isoToLoc(startMouse);
    if(goodLocation(location)){
        if(map->getCase(location)->isField()){
            dynamic_cast<ClientField*>(map->getCase(location))->setShowOwnerColor(true);
       }
    }
   if(goodLocation(previousSelectedLocation) && !previousSelectedLocation.isEqual(location)){
        if(map->getCase(previousSelectedLocation)->isField()){
            dynamic_cast<ClientField*>(map->getCase(previousSelectedLocation))->setShowOwnerColor(false);
        }
    }
    previousSelectedLocation = location;
    signaler->repaintView();
}

bool CityLordView::goodLocation(Location location){
    return map != nullptr && location.getRow() > -1 && location.getRow() < map->getNumberOfRows() &&\
           location.getCol() > -1 && location.getCol() < map->getNumberOfCols();
}


void CityLordView::mouseReleaseEvent(QMouseEvent * e){
    /*QPixmap b("src/resources/img/museum_purple.png");
    itemtest->setPixmap(b);

    QPointF pt = mapToScene(e->pos());
    scale(1.2, 1.2);
    std::cout<<"RELEASE"<<std::endl;
    rotate(-10);*/

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
}

void CityLordView::wheelEvent(QWheelEvent* e){
    if(e->delta() > 0){
        scale(1.1, 1.1);
    }
    else if(e->delta() < 0){
        scale(0.9, 0.9);
    }
}

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

void CityLordView::repaintView(){
    QPixmap pixmap;
    for(int row=0;row<map->getNumberOfRows();row++){
        for(int col=0;col<map->getNumberOfCols();col++){
            pixmap = QPixmap(getImagePath(map->getCase(Location(row, col))->getImageName()));
            itemArray[row][col]->setPixmap(pixmap);
            itemArray[row][col]->setOffset(carToIso(Location(row, col), pixmap));
        }
    }
}
