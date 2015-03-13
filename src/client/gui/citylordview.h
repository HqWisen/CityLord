#ifndef CITYLORDVIEW_H
#define CITYLORDVIEW_H

#include <QtCore>
#include <QObject>
#include <QtGui>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "repaintsignaler.h"
#include "../../common/models/Case.hpp"
#include "../../common/models/Map.hpp"
#include "clientmanagerGUI.h"


class CityLordView : public QGraphicsView{

static const int WIDTH, HEIGHT;
const QPixmap BASE;
QGraphicsScene* scene;

public:
    CityLordView(QWidget*);
    virtual ~CityLordView();
    void addBaseOn(int, int);
    void addBar();
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    void keyPressEvent(QKeyEvent *event);
    bool goodLocation(Location);
    void setClientManager(ClientManagerGUI*);
    void repaintView();
    Location isoToLoc(QPointF);
    const char* getImagePath(std::string);
    void selectField(Location);


private:
    QPointF carToIso(Location, const QPixmap&);
private:
    int px, py;
    QPointF lastPos;
    Location previousSelectedLocation;
    QPointF startMouse;
    ClientManagerGUI* clientManager;
    QGraphicsPixmapItem*** itemArray;

};

#endif // CITYLORDVIEW_H

