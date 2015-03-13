#ifndef CITYLORDVIEW_H
#define CITYLORDVIEW_H

#include <QtCore>
#include <QObject>
#include <QtGui>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "../../common/models/Case.hpp"
#include "../../common/models/Map.hpp"


class CityLordView : public QGraphicsView{

static const int WIDTH, HEIGHT;

QGraphicsScene* scene;
const QPixmap BASE, OUT;

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
    const char* getImagePath(std::string);
    void repaint(Map<ClientField>*);
    //Location isoToLoc(QPointF );  bug
    void isoToLoc(QPointF );

private:
    QPointF carToIso(Location, const QPixmap&);
    //QPointF isoToCar(int, int);
private:
    QGraphicsPixmapItem* itemArray[20][20];
    int px, py;
    QPointF lastPos;
    QPointF startMouse;
    QGraphicsPixmapItem* item;
};

#endif // CITYLORDVIEW_H

