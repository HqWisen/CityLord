#ifndef DEFAULTWIDGET_H
#define DEFAULTWIDGET_H

#include "clientmanagerGUI.h"
#include <QWidget>
#include <QFrame>

class DefaultWidget : public QWidget{
    Q_OBJECT
public:
    DefaultWidget(QWidget*, ClientManagerGUI*);
    virtual ~DefaultWidget();
    void displayDefaultBackground();
    void displayLogo(QWidget *,int, int);
    virtual void refresh() = 0;
protected:
    ClientManagerGUI* clientManager;
   QFrame backgroundFrame;
};

#endif // DEFAULTWIDGET_H
