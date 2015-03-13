#ifndef CITYLORDVIEW_H
#define CITYLORDVIEW_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "../../common/models/Case.hpp"


class CityLordView : public QGraphicsView{

static const int WIDTH, HEIGHT;

QGraphicsScene* scene;
const QPixmap BASE, OUT;

public:
    CityLordView(QWidget*);
    ~CityLordView();
    void addBaseOn(int, int);
    void addBar();
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    void keyPressEvent(QKeyEvent *event);
    const char* getImagePath(std::string);
    void display(Case*);

    //Location isoToLoc(QPointF );  bug
    void isoToLoc(QPointF );

private:
    QPointF carToIso(Location, const QPixmap&);
    //QPointF isoToCar(int, int);
private:
    //QPixmap pixmapArray[20][20];
    int px, py;
    QPointF lastPos;
    QPointF startMouse;
};

#endif // CITYLORDVIEW_H

