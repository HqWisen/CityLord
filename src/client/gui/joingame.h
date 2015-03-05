#ifndef JOINGAME_H
#define JOINGAME_H

#include <QWidget>

#include "defaultwidget.h"

namespace Ui {
class JoinGame;
}

class JoinGame : public DefaultWidget
{
    Q_OBJECT

public:
    JoinGame(QWidget*, ClientManager*);
    ~JoinGame();
    void refresh() override;

private slots:
    void on_cancelButton_clicked();

private:
    Ui::JoinGame *ui;
};


#endif // JOINGAME_H
