#ifndef CITYLORDVIEW_H
#define CITYLORDVIEW_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class CityLordView : public QGraphicsView{

static const int WIDTH, HEIGHT;

QGraphicsScene* scene;
const QPixmap BASE;

public:
    CityLordView(QWidget*);
    ~CityLordView();
    void addBaseOn(int, int);
    void addBar();
    //void addBaseOn(QPointF);
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    //void contextMenuPolicy()Event(QContextMenuEvent*) override;
    //void mouse
    void keyPressEvent(QKeyEvent *event);

private:
    QPointF carToIso(int, int, int);
    //QPointF isoToCar(int, int);

};

#endif // CITYLORDVIEW_H

