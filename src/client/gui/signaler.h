#ifndef SIGNALER_H
#define SIGNALER_H

#include <QObject>
#include "../../common/models/Location.hpp"

class Signaler : public QObject
{
    Q_OBJECT
public:
    explicit Signaler();
    void signalRepainting();
    void signalBuildViewMap();
    void signalActiving(std::string, Location);
signals:
    void repaintView();
    void buildViewMap();
    void activeButton(std::string, Location);
public slots:

};

#endif // SIGNALER_H
