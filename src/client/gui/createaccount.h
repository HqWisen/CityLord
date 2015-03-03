#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H


#include "defaultwidget.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public DefaultWidget{
    Q_OBJECT
public:
    CreateAccount(QWidget*, WidgetManager*);
    ~CreateAccount();
    void refresh() override;
private slots:
    void on_cancelButton_clicked();
    //void on_createButton_clicked();

private:
    Ui::CreateAccount *ui;
};

#endif // CREATEACCOUNT_H
