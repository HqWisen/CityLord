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
signals:
    void repaintView();
    void buildViewMap();
    void selectField(SocketMessage, Location);
    void updateMoney(int);
public slots:

};

#endif // SIGNALER_H
