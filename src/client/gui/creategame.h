#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "defaultwidget.h"

namespace Ui {
class CreateGame;
}

class CreateGame : public DefaultWidget{
    Q_OBJECT
public:
    CreateGame(QWidget*, WidgetManager*);
    ~CreateGame();
    void refresh() override;
private slots:
    void on_cancelButton_clicked();

private:
    Ui::CreateGame *ui;
};

#endif // CREATEGAME_H
