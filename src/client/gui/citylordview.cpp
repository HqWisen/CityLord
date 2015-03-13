#include "citylordview.h"
#include <iostream>

const int CityLordView::WIDTH = 1152;
const int CityLordView::HEIGHT = 804;



CityLordView::CityLordView(QWidget* parent):
    QGraphicsView(parent), BASE(getImagePath("base")), scene(new QGraphicsScene(this)), previousSelectedLocation(-1, -1), clientManager(nullptr) {
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

void CityLordView::selectField(Location location){
    clientManager->setRequest("selectfield");
    clientManager->addInfo("row", std::to_string(location.getRow()));
    clientManager->addInfo("col", std::to_string(location.getCol()));
    clientManager->sendRequestAndRecv();
    clientManager->getRepaintSignaler()->signalActiving(clientManager->getMessage().getTopic(), location);
}

void CityLordView::mousePressEvent(QMouseEvent * e){

    startMouse = mapToScene(e->pos());
    Location location = isoToLoc(startMouse);
    if(goodLocation(location)){
        selectField(location);
        if(clientManager->getMap()->getCase(location)->isField()){
            dynamic_cast<ClientField*>(clientManager->getMap()->getCase(location))->setShowOwnerColor(true);
       }
    }
   if(goodLocation(previousSelectedLocation) && !previousSelectedLocation.isEqual(location)){
        if(clientManager->getMap()->getCase(previousSelectedLocation)->isField()){
            dynamic_cast<ClientField*>(clientManager->getMap()->getCase(previousSelectedLocation))->setShowOwnerColor(false);
        }
    }
    previousSelectedLocation = location;
    clientManager->getRepaintSignaler()->repaintView();
}

bool CityLordView::goodLocation(Location location){
    return clientManager->getMap() != nullptr && location.getRow() > -1 && location.getRow() < clientManager->getMap()->getNumberOfRows() &&\
           location.getCol() > -1 && location.getCol() < clientManager->getMap()->getNumberOfCols();
}


void CityLordView::mouseReleaseEvent(QMouseEvent * e){

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
    /*switch(event->key()){
        case Qt::Key_Up:
            py-=30;
            lastPos.setY(lastPos.y() - 30);
            setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);
            break;
        case Qt::Key_Left:
            px-=30;
            lastPos.setX(lastPos.x() - 30);
            setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);
            break;
        case Qt::Key_Right:
            px+=30;
            lastPos.setX(lastPos.x() +30);
            setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);
            break;
        case Qt::Key_Down:
            py+=30;
            lastPos.setY(lastPos.y() + 30);
            setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);
            break;
    }*/
}

void CityLordView::setClientManager(ClientManagerGUI* cm){
    clientManager = cm;
}

void CityLordView::repaintView(){
    QPixmap pixmap;
    for(int row=0;row<clientManager->getMap()->getNumberOfRows();row++){
        for(int col=0;col<clientManager->getMap()->getNumberOfCols();col++){
            pixmap = QPixmap(getImagePath(clientManager->getMap()->getCase(Location(row, col))->getImageName()));
            itemArray[row][col]->setPixmap(pixmap);
            itemArray[row][col]->setOffset(carToIso(Location(row, col), pixmap));
        }
    }
}
