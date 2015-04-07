#ifndef SIGNALER_H
#define SIGNALER_H

#include <QObject>
#include "../../common/models/Location.hpp"
#include "../../common/socket/SocketMessage.hpp"
class Signaler : public QObject
{
    Q_OBJECT
public:
    explicit Signaler();
    void signalRepainting();
    void signalBuildViewMap();
    void signalActiving(SocketMessage, Location);
    void signalUpdatingMoney(int);
    void signalUpdatingTime(std::string);
    void signalCreatingVisitor(int, Location);
    void signalMovingVisitor(int, Location);
    void signalRemovingVisitor(int);
signals:
    void repaintView();
    void buildViewMap();
    void selectField(SocketMessage, Location);
    void updateMoney(int);
    void updateTime(QString);
    void createVisitor(int, QString);
    void moveVisitor(int, QString);
    void removeVisitor(int);
public slots:

};

#endif // SIGNALER_H
