#ifndef CITYLORDVIEW_H
#define CITYLORDVIEW_H

#include <QtCore>
#include <QObject>
#include <QtGui>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "signaler.h"
#include "../../common/models/Case.hpp"
#include "../../common/models/Map.hpp"
#include "clientmanagerGUI.h"


class CityLordView : public QGraphicsView{

static const int WIDTH, HEIGHT, DEFAULTZOOMLEVEL;
int ZOOMLEVEL,COORDX,COORDY;
const QPixmap BASE;
QGraphicsScene* scene;

public:
    CityLordView(QWidget*, ClientManagerGUI*);
    virtual ~CityLordView();
    void cleanItemArray();
    void createVisitor(Location);
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    void keyPressEvent(QKeyEvent *event);
    bool goodLocation(Location);
    void centerMap();
    void repaintView();
    void buildViewMap();
    Location isoToLoc(QPointF);
    const char* getImagePath(std::string);
    void selectField(Location);    
    void showCurrentPlayerFieldColor();
    void showAllFieldColor();
    void unshowAllFieldColor();

private:
    QPointF carToIso(Location, const QPixmap&);
    void showFieldColor(bool, bool);
private:
    int px, py;
    QPointF lastPos;
    Location previousSelectedLocation;
    QPointF startMouse;
    ClientManagerGUI* clientManager;
    int numberOfRows, numberOfCols;
    QGraphicsPixmapItem*** itemArray;

};

#endif // CITYLORDVIEW_H

