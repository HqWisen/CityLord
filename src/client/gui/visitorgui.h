#ifndef VISITORGUI_H
#define VISITORGUI_H

#include <QtCore>
#include <QObject>
#include <QtGui>
#include <QThread>
#include <QMutex>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include "../../common/models/Location.hpp"

class VisitorGUI : public QThread{
    Q_OBJECT
    QMutex movemutex;
    const QPixmap NORTH, SOUTH, EAST, WEST;
public:
    explicit VisitorGUI(QObject* parent, QGraphicsScene*);
    ~VisitorGUI();
    void run() override;
    void show(Location);
    void move(Location);
    void remove();
    QPointF carToIso(Location, const QPixmap&);
    const char* getImagePath(std::string);
signals:
public slots:
private:
    bool moving;
    Location nextLocation, currentLocation;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* item;
};

#endif // VISITORGUI_H
