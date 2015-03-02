#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, WidgetManager* wm) :
    QWidget(parent), ui(new Ui::MainMenu), widgetManager(wm)
{
    QWidget *frame = new QWidget(this);
    frame->setGeometry(0, 0, 1152, 864);
    frame->setStyleSheet("background-image: url("+QCoreApplication::applicationDirPath() + "/BgCityBig.jpg"+")");

    /*QWidget *frame2 = new QWidget(this);
    frame2->setGeometry(350, 100, 500, 200);
    frame2->setStyleSheet("background-image: url("+QCoreApplication::applicationDirPath() + "/CityLordsmall.png"+")");*/

    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

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
