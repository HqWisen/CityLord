#ifndef REPAINTSIGNALER_H
#define REPAINTSIGNALER_H

#include <QObject>

class RepaintSignaler : public QObject
{
    Q_OBJECT
public:
    explicit RepaintSignaler();
    void signalRepainting();
signals:
    void repaintView();
public slots:

};

#endif // REPAINTSIGNALER_H
