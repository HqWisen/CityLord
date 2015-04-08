#ifndef VISITORGUI_H
#define VISITORGUI_H

#include <QtCore>
#include <QObject>
#include <QtGui>
#include "QThread"
#include <QMutex>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include "../../common/models/Location.hpp"
#include "clientmanagerGUI.h"

class VisitorGUI : QGraphicsPixmapItem{
    QMutex movemutex, inmutex;
    const QPixmap NORTH, SOUTH, EAST, WEST;
public:
    explicit VisitorGUI(ClientManagerGUI*, QGraphicsScene*);
    ~VisitorGUI();
    //void run() override;
    void changeImage(Location, Location);
    void show(Location);
    void advance(int) override;
    void move(Location);
    void remove();
    //void abort();
    QPointF carToIso(Location, const QPixmap&);
    const char* getImagePath(std::string);
signals:
public slots:
private:
    bool moving, in, arrived;
    int counter;
    Location nextLocation, currentLocation;
    ClientManagerGUI* clientManager;
    QGraphicsScene* scene;
    QPointF pstart, pend, current;
    qreal stepx, stepy;
    static const int MAXSTEP;

};

#endif // VISITORGUI_H
