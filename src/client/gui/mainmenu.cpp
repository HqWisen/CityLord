#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, WidgetManager* wm) :
    DefaultWidget(parent, wm), ui(new Ui::MainMenu){

    displayDefaultBackground();
    ui->setupUi(this);
}

MainMenu::~MainMenu(){
    delete ui;
}

void MainMenu::refresh(){
}

/*
void MainMenu::on_join_pushButton_clicked()
{
    QMessageBox::warning(this, "Join", "Make a Join Function");
}

void MainMenu::on_create_pushButton_clicked()
{
    QMessageBox::warning(this, "Create", "Make a Create Function");
}

void MainMenu::on_disconnect_pushButton_clicked()
{
    QMessageBox::warning(this, "Disconnect", "Make a Disconnect Function");
}

void MainMenu::on_quit_pushButton_clicked()
{
    QMessageBox::warning(this, "Quit", "Make a Quit Function");
}
*/
