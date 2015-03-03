#ifndef DEFAULTWIDGET_H
#define DEFAULTWIDGET_H

#include "widgetmanager.h"
#include <QWidget>
#include <QFrame>

class DefaultWidget : public QWidget{
    Q_OBJECT
public:
    DefaultWidget(QWidget*, WidgetManager*);
    virtual ~DefaultWidget();
    void displayDefaultBackground();
    virtual void refresh() = 0;
protected:
    WidgetManager* widgetManager;
   QFrame backgroundFrame;
};

#endif // DEFAULTWIDGET_H
