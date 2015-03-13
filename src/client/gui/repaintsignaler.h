#ifndef REPAINTSIGNALER_H
#define REPAINTSIGNALER_H

#include <QObject>
#include "../../common/models/Location.hpp"

class RepaintSignaler : public QObject
{
    Q_OBJECT
public:
    explicit RepaintSignaler();
    void signalRepainting();
    void signalActiving(std::string, Location);
signals:
    void repaintView();
    void activeButton(std::string, Location);
public slots:

};

#endif // REPAINTSIGNALER_H
