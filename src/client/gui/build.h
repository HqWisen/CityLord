#ifndef BUILD_H
#define BUILD_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "clientmanagerGUI.h"

namespace Ui {
class build;
}

class build : public QDialog{
    Q_OBJECT
public:
    explicit build(QWidget*, ClientManagerGUI*);
    ~build();
    void refresh();
    QPushButton* getCancelButton();
private slots:
   void on_buildButton_clicked();
   void on_cancelButton_clicked();

private:
   Ui::build* ui;
   ClientManagerGUI* clientManager;
   QTableWidgetItem** tableItemArray;
   QStringList headerLabels;
   int choice;
};
#endif // BUILD_H
