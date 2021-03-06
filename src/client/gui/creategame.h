#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "defaultwidget.h"
#include <QMessageBox>

namespace Ui {
class CreateGame;
}

class CreateGame : public DefaultWidget{
    Q_OBJECT
    static const std::string MAP1PICTURE, MAP2PICTURE, MAP3PICTURE;
    static const std::string CLICKCOLOR, UNCLICKCOLOR;
    int gameMode;
public:
    CreateGame(QWidget*, ClientManagerGUI*);
    ~CreateGame();
    void refresh() override;
private slots:
    void on_map1Button_clicked();
    void on_map2Button_clicked();
    void on_map3Button_clicked();
    void on_createButton_clicked();
    void on_cancelButton_clicked();
    void on_gameModeSelect_currentIndexChanged(int index);
    void changedGameMode();

private:
    QString getStyleSheet(std::string, std::string);

private:
    Ui::CreateGame *ui;
    int choice;
};

#endif // CREATEGAME_H
