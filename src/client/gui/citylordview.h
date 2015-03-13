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
    void repaintView();
    Location isoToLoc(QPointF);
    void setPlayedMap(Map<ClientField>*);
    void setRepaintSignaler(RepaintSignaler*);
    const char* getImagePath(std::string);

private:
    QPointF carToIso(Location, const QPixmap&);
private:
    int px, py;
    QPointF lastPos;
    Location previousSelectedLocation;
    QPointF startMouse;
    Map<ClientField>* map;
    RepaintSignaler* signaler;
    QGraphicsPixmapItem*** itemArray;

};

#endif // CITYLORDVIEW_H

