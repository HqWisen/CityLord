#ifndef INPLAY_H
#define INPLAY_H

#include "widgetmanager.h"
#include <QWidget>
#include <QMessageBox>

namespace Ui {
class InPlay;
}

class InPlay : public QWidget
{
    Q_OBJECT

public:
    explicit InPlay(QWidget *parent, WidgetManager*);
    ~InPlay();

private slots:
    void on_build_pushButton_clicked();

    void on_upgrade_pushButton_clicked();

    void on_sell_pushButton_clicked();

    void on_demolish_pushButton_clicked();

private:
    Ui::InPlay *ui;
    WidgetManager* widgetManager;

};

#endif // INPLAY_H
