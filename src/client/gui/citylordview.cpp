#include "citylordview.h"
#include <iostream>

const int CityLordView::WIDTH = 1152;
const int CityLordView::HEIGHT = 804;
const int CityLordView::DEFAULTZOOMLEVEL = 10;

CityLordView::CityLordView(QWidget* parent, ClientManagerGUI* cm):
    QGraphicsView(parent), BASE(getImagePath("base")), scene(new QGraphicsScene(this)), previousSelectedLocation(-1, -1), clientManager(cm), numberOfRows(0),  \
    numberOfCols(0), itemArray(nullptr){
    setGeometry(0, 60, WIDTH, HEIGHT);
    resize(WIDTH, HEIGHT);
    setScene(scene);
    setSceneRect(-((WIDTH/2)-(BASE.width()/2)), 0, WIDTH-2, HEIGHT-2);
    this->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ZOOMLEVEL=DEFAULTZOOMLEVEL;
    COORDX=1520;
    COORDY=0;

    /*****/
    int WIDTHOUT = 30;
    QPixmap pixmap;
    for(int row=-WIDTHOUT;row<100+WIDTHOUT;row++){
        for(int col=-WIDTHOUT;col<100+WIDTHOUT;col++){
            pixmap = QPixmap(getImagePath("out"));
            scene->addPixmap(pixmap)->setOffset(carToIso(Location(row, col), pixmap));
        }
    }
}

CityLordView::~CityLordView(){
    cleanItemArray();
    delete scene;
}

void CityLordView::cleanItemArray(){
    if(itemArray != nullptr){
        for(int row=0;row<numberOfRows;row++){
            for(int col=0;col<numberOfCols;col++){
                scene->removeItem(itemArray[row][col]);
                delete itemArray[row][col];
            }
        }
    }
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
    clientManager->getSignaler()->signalActiving(clientManager->getMessage(), location);
}

void CityLordView::showCurrentPlayerFieldColor(){
    showFieldColor(false, true);
    showFieldColor(true, false);
    repaintView();
}

void CityLordView::showAllFieldColor(){
    showFieldColor(false, true);
    showFieldColor(true, true);
    repaintView();
}

void CityLordView::unshowAllFieldColor(){
    showFieldColor(false, true);
    repaintView();
}

void CityLordView::showFieldColor(bool show, bool allPlayers = true){
     ClientField* field;
    for(int row=0;row<numberOfRows;row++){
        for(int col=0;col<numberOfCols;col++){
            if((field = dynamic_cast<ClientField*>(clientManager->getMap()->getCase(Location(row, col))))){
                if(allPlayers || clientManager->getCurrentPlayerID() == field->getOwnerID()){
                    field->setShowOwnerColor(show);
                }
            }
        }
    }
}

void CityLordView::mousePressEvent(QMouseEvent * e){
    showFieldColor(false, true);
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
    repaintView();
}

bool CityLordView::goodLocation(Location location){
    return clientManager->getMap() != nullptr && location.getRow() > -1 && location.getRow() < clientManager->getMap()->getNumberOfRows() &&\
           location.getCol() > -1 && location.getCol() < clientManager->getMap()->getNumberOfCols();
}


void CityLordView::mouseReleaseEvent(QMouseEvent * e){

}

void CityLordView::mouseMoveEvent(QMouseEvent * e){
    QPointF currentPos = mapToScene(e->pos());
    if(startMouse.x() < currentPos.x() and currentPos.x()>-1520){   // -rows*baselength
        int move = currentPos.x()-startMouse.x();
        px-= move;
        lastPos.setX(lastPos.x()-move);
    }else if(startMouse.x() > currentPos.x() and currentPos.x()<1520){  // rows*baselength
        int move = startMouse.x()-currentPos.x();
        px+= move;
        lastPos.setX(lastPos.x()+move);
    }
    if(startMouse.y() < currentPos.y() and currentPos.y()>0){   // 0
        int move = currentPos.y()-startMouse.y();
        py-=move;
        lastPos.setY(lastPos.y()-move);
    }else if(startMouse.y() > currentPos.y() and currentPos.y()<1500){// columns*baseheight
        int move = startMouse.y()-currentPos.y();
        py+=move;
        lastPos.setY(lastPos.y()+move);
    }
    lastPos = currentPos;
    setSceneRect(-((WIDTH/2)-(BASE.width()/2))+px, py, WIDTH-2, HEIGHT-2);
}

void CityLordView::wheelEvent(QWheelEvent* e){
    if(e->delta() > 0 and ZOOMLEVEL<DEFAULTZOOMLEVEL+10){
        ZOOMLEVEL+=1;
        scale(1.1, 1.1);
    }
    else if(e->delta() < 0 and ZOOMLEVEL>DEFAULTZOOMLEVEL-10){
        ZOOMLEVEL-=1;
        scale(0.9, 0.9);
    }
    std::cout<<scene->height()<<std::endl;
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

void CityLordView::buildViewMap(){

    /**********************/
    //scale(0.35, 0.35);
    if(clientManager == nullptr){
        throw std::invalid_argument("clientManager is nullptr in the view.");
    }else{

        cleanItemArray();
        numberOfRows = clientManager->getMap()->getNumberOfRows();
        numberOfCols = clientManager->getMap()->getNumberOfCols();
        itemArray = new QGraphicsPixmapItem**[numberOfRows];
        for(int i=0;i<numberOfRows;i++){
            itemArray[i] = new QGraphicsPixmapItem*[numberOfCols];
            for(int j=0;j<numberOfCols;j++){
                itemArray[i][j] = new QGraphicsPixmapItem;
                scene->addItem(itemArray[i][j]);
            }
        }
    }
    repaintView();
}
