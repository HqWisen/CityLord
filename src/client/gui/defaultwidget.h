#ifndef DEFAULTWIDGET_H
#define DEFAULTWIDGET_H

#include "clientmanager.h"
#include <QWidget>
#include <QFrame>

class DefaultWidget : public QWidget{
    Q_OBJECT
public:
    DefaultWidget(QWidget*, ClientManager*);
    virtual ~DefaultWidget();
    void displayDefaultBackground();
    virtual void refresh() = 0;
protected:
    ClientManager* clientManager;
   QFrame backgroundFrame;
};

#endif // DEFAULTWIDGET_H
